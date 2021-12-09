//
// Created by ZitengShu on 12/8/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_MULACO_H
#define PARALLEL_ANT_COLONY_SYSTEM_MULACO_H
#pragma once
#include "../sequential/model.h"
#include "../utils/communicator.h"
#include "../utils/topology.h"
#include <mpi.h>

class MulACO: public Model{
public:
    MulACO(int number_of_ants, double initial_alpha, double initial_beta, double initial_q,
           double initial_rho, Dataloader *p_dataloader, int proc_id, int number_of_proc);
    ~MulACO();
    void solve(int max_itr);
    void communication(Solution &local_best);
    void collect_global_best();
    int rank, nproc;
    Communicator communicator;
    Topology ring;
};


#endif //PARALLEL_ANT_COLONY_SYSTEM_MULACO_H
