15618 Final Project (Parallel Ant Colony System)

## Code Structure
```
Parallel-Ant-Colony-System/
├── Makefile
├── README.md
├── scripts
│   ├── mpiaco_test.sh
│   ├── profiler.py
│   ├── requirement.txt
│   ├── start_test.sh
│   └── visualizer.py
├── src
│   ├── main.cpp
│   ├── mpiaco
│   │   ├── mpiaco.cpp
│   │   └── mpiaco.h
│   ├── mulaco
│   │   ├── mulaco.cpp
│   │   └── mulaco.h
│   ├── paco
│   │   ├── paco.cpp
│   │   └── paco.h
│   ├── sequential
│   │   ├── ant.cpp
│   │   ├── ant.h
│   │   ├── dataloader.cpp
│   │   ├── dataloader.h
│   │   ├── model.cpp
│   │   ├── model.h
│   │   ├── path.cpp
│   │   ├── path.h
│   │   ├── random.cpp
│   │   ├── random.h
│   │   ├── solution.cpp
│   │   ├── solution.h
│   │   ├── tabu.cpp
│   │   ├── tabu.h
│   │   ├── timer.cpp
│   │   └── timer.h
│   └── utils
│       ├── communicator.cpp
│       ├── communicator.h
│       ├── topology.cpp
│       └── topology.h
└── tests
```

## Output file format (./output/\<dataset\>/\<dataset\>\_\<model\>\_\<n_cores\>)
NAME : \<name\>

DISTANCE: \<distance\>

DIMENSION : \<dimension\>

\<output positions\>

...

## Output profile format (./output/\<dataset\>/\<dataset\>\_\<model\>\_\<profile\>)
COMPUTATION TIME (\<number of cores\>) : 2.3

TOUR_LENGTH (\<number of cores\>) : 500

...


## Visualizer and profiler

```
python3 scripts/visualizer.py -f output/<dataset>/<dataset>_<n_cores>
python3 scripts/profiler.py -f output/<dataset>/<dataset>_profile
```
