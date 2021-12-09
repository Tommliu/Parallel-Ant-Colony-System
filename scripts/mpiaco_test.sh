#!/usr/bin/bash

# rm ./output/*/*_profile
total_iteration=256
for i in 1 2 4 8 16
do
  iter=$(expr $total_iteration / $i)
  mpirun -np $i ./build/bin/aco -f tests/xqf131.tsp -m 2 -c $i -n 200 -i $iter
  ./scripts/visualizer.py -f ./output/xqf131/xqf131_$i
done
./scripts/profiler.py -f ./output/xqf131/xqf131_profile