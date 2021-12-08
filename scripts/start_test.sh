#!/usr/bin/bash

rm ./output/*/*_profile
for i in 1 2 4 8 16
do
  ./build/bin/aco -f tests/xqf131.tsp -m 1 -c $i
  ./scripts/visualizer.py -f ./output/xqf131/xqf131_$i
done

./scripts/profiler.py -f ./output/xqf131/xqf131_profile