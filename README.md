15618 Final Project (Parallel Ant Colony System (Optimization))

By Minghao Liu and Ziteng Shu

## SUMMARY
We are going to implement multiple versions of parallel implementations of the Ant Colony Optimization(ACO) on multi-core CPU platforms, compare and analyze the trade-off and performance across these methods. OpenMP and OpenMPI will be used in this project.
As various approaches(parallel models) have been conducted with different emphasis.
A detailed analysis will be useful and necessary. Here in this project, we are considering three factors: number of colonies, cooperation mode and granularity.



## BACKGROUND
**Algorithm explanation**:
The Ant Colony Optimization is a class of optimization algorithms that was modeled by the behavior of real ants.  Artificial 'ants' (e.g. simulation agents) locate optimal solutions by moving through a parameter space representing all possible solutions. And ants will leave pheromones to influence the exploration of others. The evaluation of the solution will decide how pheromones are preserved. The application that built on the algorithm will be the classic Travelling salesman problem (Vehicle routing problem). Given a graph of cities with different weights on the edge (distance), we should find the approximate optimal solution in this sense. The high level pseudocode is as following:

```
procedure ACO_MetaHeuristic is
    while not terminated do
        generateSolutions()
        daemonActions()
        pheromoneUpdate()
    repeat
end procedure
```
The generateSolutions() function will mainly take advantage of some heuristic function to generate a path. The dameonActions() function will mainly compare the paths found by different “ants”. Finally the pheromoneUpdate() function will update the pheromone information that is shared across the “ants”.  Since the ant colony algorithm relies on “ants” exploring a large search space, the computation is too heavy for the sequential implementation. Thus, parallel design should naturally fit into the implementation. Following is a graph of categorized different Ant colony Optimization on CPU. Our project will focus on implementing and analyzing these approaches.

![A hierarchical view of parallel approaches]()


## CHALLENGE 
1.  Since our project is focusing on analyzing various parallel models based on OpenMP and OpenMPI. There will be plenty of implementation requirements throughout the process. Table 1 describes the models we are going to implement.

| Model                     | Population organization       | \# Colonies | \# Pheromone matrices | Communication frequency |
| ------------------------- | ----------------------------- | ----------- | --------------------- | ----------------------- |
| Coarse-grain master-slave | Hierarchical, non-cooperative | One         | One                   | Medium                  |
| Medium-grain master-slave | Hierarchical, non-cooperative | One         | One                   | Medium-High             |
| Fine-grain master-slave   | Hierarchical, non-cooperative | One         | One                   | High                    |
| Cellular                  | Structured, cooperative       | One         | Many                  | Medium                  |
| Parallel independent runs | Distributed, non-cooperative  | Several     | Several               | Zero                    |
| Multicolony               | Distributed, cooperative      | Several     | Several               | Low                     |
| Hybrids                   | Hierarchical                  | D/P         | D/P                   | D/P                     |

2.  As is stated in the ACO, the pheromone is shared across the colonies through the graph. During cooperation mode, how to share and update the pheromone effectively by shared memory model and message passing model is a challenge.

3. For OpenMPI, we have limited cores. How to design the colony size and divide the workload is one of the crucial factors that affect the computation performance.

## RESOURCES
Describe the resources (type of computers, starter code, etc.) you will use.
What code base will you start from? Are you starting from scratch or using an existing
piece of code? Is there a book or paper that you are using as a reference (if so, provide a
citation)? Are there any other resources you need, but haven’t figured out how to obtain
yet? Could you benefit from access to any special machines?

## GOALS AND DELIVERABLES
Describe the deliverables or goals of your project

## PLATFORM CHOICE
Describe why the platform (computer and/or language) you have
chosen is a good one for your needs. Why does it make sense to use this parallel system
for the workload you have chosen?

## SCHEDULE

#### Nov.5 - Nov.11 (week1)
* Read papers to learn the details of ... implementation.

#### Nov.12 - Nov.18 (week2)
* Implement ...
 
#### Nov.19 - Nov.25 (week3)
*  ...

#### Nov.26 - Dec.1 (week4)
* ....

#### Dec.1 - Dec.5 (week5)
* ....

#### Dec.5 - Dec.9 (week6)
* ....

## REFERENCE
