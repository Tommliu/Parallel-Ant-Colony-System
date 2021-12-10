#!/usr/bin/env bash
#draw images
# xqf131/xql662/xqd4966
for i in 1 2 3
do
    for j in 1 2 4 8 16
    do
      ./scripts/visualizer.py -f ./output/xqd4966/xqd4966_${i}_${j}
    done
    ./scripts/profiler.py -f ./output/xqd4966/xqd4966_${i}_profile
done