#!/usr/bin/env bash

rm ./output/xqf131/*_profile

# openmp and openmpi
for i in 16 8 4 2 1
do
  # openmp mode=1
  ./build/bin/aco -f tests/xqf131.tsp -m 1 -c $i -n 200 -i 240
  # openmpi mode=2
  mpirun -np $i ./build/bin/aco -f tests/xqf131.tsp -n 200 -i $(expr 240 / $i) -m 2
  # openmpi mode=3
  mpirun -np $i ./build/bin/aco -f tests/xqf131.tsp -n 200 -i $(expr 240 / $i) -m 3
done