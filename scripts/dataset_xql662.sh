#!/usr/bin/env bash

rm ./output/xql662/*_profile

# openmp and openmpi
for i in 16 8 4 2 1
do
  # openmp mode=1
  ./build/bin/aco -f tests/xql662.tsp -m 1 -c $i -n 1000 -i 240
  # openmpi mode=2
  mpirun -np $i ./build/bin/aco -f tests/xql662.tsp -n 1000 -i $(expr 240 / $i) -m 2
  # openmpi mode=3
  mpirun -np $i ./build/bin/aco -f tests/xql662.tsp -n 1000 -i $(expr 240 / $i) -m 3
done