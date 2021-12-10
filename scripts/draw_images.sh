#!/usr/bin/env bash
#draw images
# xqf131/xql662/xqd4966
for i in 1 2 3
do
    for j in 1 2 4 8 16 32 64 96
    do
      ./scripts/visualizer.py -f ./output/xql662/xql662_${i}_${j}
    done
    ./scripts/profiler.py -f ./output/xql662/xql662_${i}_profile
done