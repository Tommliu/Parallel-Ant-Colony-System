#ifndef PARALLEL_ANT_COLONY_SYSTEM_MPIACO_H
#define PARALLEL_ANT_COLONY_SYSTEM_MPIACO_H
#pragma once
#include "../sequential/model.h"
#include <string.h>
#include "mpi.h"

class MPIACO : public Model {
public:
    MPIACO(int number_of_ants, int procID, int nproc, double initial_alpha, double initial_beta, double initial_q,
            double initial_rho, int max_iteration, Dataloader *p_dataloader);
    ~MPIACO();
    int init_ants(int procID, int nproc, int number_of_ants);
    void update_pheromone();

    int myrank_;
    int nproc_;
    char *sync_data;
};

#endif // PARALLEL_ANT_COLONY_SYSTEM_MPIACO_H
