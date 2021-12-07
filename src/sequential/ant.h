//
// Created by ZitengShu on 11/21/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_ANT_H
#define PARALLEL_ANT_COLONY_SYSTEM_ANT_H
#pragma once
#include <cmath>

#include "path.h"
#include "tabu.h"
class Ant {
public:
    Ant();
    void initialize(int number_of_cities);
    void release();
    void visit_city(int index, int city);
    void reset();
    double get_length(Dataloader *dataloader);
    void update_probe(int start, int n_cities, Dataloader *dataloader,
                      double **phero, double alpha, double beta);

    virtual void update_pheromone(double **phero, double Q, Dataloader *dataloader);
    virtual ~Ant();

    Path path;
    Tabu tabu_list;
    double *probe;
};


#endif //PARALLEL_ANT_COLONY_SYSTEM_ANT_H
