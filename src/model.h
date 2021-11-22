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

class Model {
public:
    Model (int number_of_ants, double initial_alpha, double initial_beta, double initial_q,
           double initial_rho, int max_iteration, Dataloader *p_dataloader);
    virtual ~Model ();

    void random_place_ants();
    void construct_routes();
    void update_pheromone();
    void pheromone_decay();
    void write_output(const char* input_path);

    void solve();

    double best_length;
    int n_ants, n_cities, max_iter;
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
    Random *random;
    Path *best_route;
    std::vector<Ant> ants;

};
#endif //PARALLEL_ANT_COLONY_SYSTEM_MODEL_H
