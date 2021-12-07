15618 Final Project (Parallel Ant Colony System)

## Output file format (./output/\<dataset\>)
NAME : ...

DIMENSION : ...

\<output positions\>

...

## Output profile format
COMPUTATION TIME (\<number of cores\>) : 2.3

TOUR_LENGTH (\<number of cores\>) : 500

...


## Visualizer and profiler

```
python3 scripts/visualizer.py -f output/<dataset>/<dataset>_<n_cores>
python3 scripts/profiler.py -f output/<dataset>/<dataset>_profile
```