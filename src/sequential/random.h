//
// Created by ZitengShu on 11/21/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_RANDOM_H
#define PARALLEL_ANT_COLONY_SYSTEM_RANDOM_H
#pragma once
#include <random>

#include "ant.h"

class Random {
public:
    Random();
    virtual ~Random();
    int get_initial_city(int n_cities);
    int get_next_city(Ant *ant, int start, int n_cities, Dataloader *dataloader,
                      double *phero, double alpha, double beta);
};


#endif //PARALLEL_ANT_COLONY_SYSTEM_RANDOM_H
