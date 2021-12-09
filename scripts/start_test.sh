#!/usr/bin/env bash

rm ./output/*/*_profile

# sequential
./build/bin/aco -f tests/xqf131.tsp -n 200 -i 240 -m 0
./scripts/visualizer.py -f ./output/xqf131/xqf131_0_1

# openmp and openmpi
for i in 16
do

  # openmp mode=1
  ./build/bin/aco -f tests/xqf131.tsp -m 1 -c $i -n 200 -i 240
  # openmpi mode=2
  mpirun -np $i ./build/bin/aco -f tests/xqf131.tsp -n 200 -i $(expr 240 / $i) -m 2
  # openmpi mode=3
  mpirun -np $i ./build/bin/aco -f tests/xqf131.tsp -n 200 -i $(expr 240 / $i) -m 3
done

#draw images
for k in 1 2 3
do
  for i in 16
  do
    ./scripts/visualizer.py -f ./output/xqf131/xqf131_$k_$i
  done
  ./scripts/profiler.py -f ./output/xqf131/xqf131_$k_profile
done
