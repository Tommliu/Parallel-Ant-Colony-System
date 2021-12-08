//
// Created by ZitengShu on 11/21/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_MODEL_H
#define PARALLEL_ANT_COLONY_SYSTEM_MODEL_H
#pragma once
#include <climits>
#include <vector>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <sys/stat.h>
#include "dataloader.h"
#include "ant.h"
#include "path.h"
#include "random.h"
#include "solution.h"

class Model {
public:
    Model();
    Model(int number_of_ants, double initial_alpha, double initial_beta, double initial_q,
           double initial_rho, Dataloader *p_dataloader);
    virtual ~Model();
    void init(double initial_alpha, double initial_beta, double initial_q,
              double initial_rho, Dataloader *p_dataloader);
    virtual void random_place_ants();
    virtual void construct_routes();
    virtual void update_pheromone();
    void pheromone_decay();
    void write_output(const char* input_path, int n_core, double duration_time);

    void solve(int max_itr);

    Solution global_best, local_best;

    int n_ants, n_cities;
    /**
     * alpha is Evaporation parameter
     * beta is Expectation Heuristic Factor
     * rho is Pheromone volatilization rate
     * Q is Pheromone intensity
     * tau is
     * */
    double alpha, beta, q, rho, tau, decay_rate;
    double **pheromone;
    Dataloader *dataloader;
    Random random;
    Ant *ants;
};
#endif //PARALLEL_ANT_COLONY_SYSTEM_MODEL_H
