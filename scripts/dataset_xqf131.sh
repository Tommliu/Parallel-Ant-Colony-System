#!/usr/bin/env bash

rm ./output/xqf131/*_profile
n_ants=2080
iteration=20
Q=200
frequency=2
# openmp and openmpi
for i in 1 2 4 8 16
do
  # openmp mode=1
  #./build/bin/aco -f tests/xqf131.tsp -m 1 -c $i -n $n_ants -i $iteration -q $Q
  # openmpi mode=2
  #mpirun -np $i ./build/bin/aco -f tests/xqf131.tsp -n $(expr $n_ants / $i) -i $iteration -m 2 -q $Q
  # openmpi mode=3
  mpirun -np $i ./build/bin/aco -f tests/xqf131.tsp -n $(expr $n_ants / $i) -i $iteration -m 3 -q $Q -y $frequency
done