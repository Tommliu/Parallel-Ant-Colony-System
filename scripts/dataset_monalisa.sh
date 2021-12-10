#!/usr/bin/env bash

n_ants=150000
iteration=1
Q=500000
# openmp
./build/bin/aco -f tests/mona-lisa100K.tsp -m 1 -c 16 -n $n_ants -i $iteration -q $Q