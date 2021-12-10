#!/usr/bin/env bash

rm ./output/xqf131/*_profile
n_cores=16
n_ants=100
iteration=512
Q=200
# openmp and openmpi
for i in 1 2 4 8 16 32 64 128 256
do
  # openmpi mode=3
  mpirun -np ${n_cores} ./build/bin/aco -f tests/xqf131.tsp -n ${n_ants} -i ${iteration} -m 3 -q ${Q} -y ${i}
done