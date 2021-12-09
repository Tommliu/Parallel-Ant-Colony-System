#!/usr/bin/env bash
#draw images
./scripts/visualizer.py -f ./output/xqf131/xqf131_0_1

for i in 1 2 3
do
    for j in 1 2 4 8 16
    do
        ./scripts/visualizer.py -f "./output/xqf131/xqf131_${i}_${j}"
    done
    ./scripts/profiler.py -f "./output/xqf131/xqf131_${i}_profile"
done