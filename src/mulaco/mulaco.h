//
// Created by ZitengShu on 12/8/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_MULACO_H
#define PARALLEL_ANT_COLONY_SYSTEM_MULACO_H
#include "../sequential/model.h"
#include "../utils/communicator.h"

class MulACO: public Model{
    MulACO(int number_of_ants, double initial_alpha, double initial_beta, double initial_q,
           double initial_rho, Dataloader *p_dataloader);
    ~MulACO();

    Communicator communicator;
};


#endif //PARALLEL_ANT_COLONY_SYSTEM_MULACO_H
