//
// Created by ZitengShu on 12/7/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_PACO_H
#define PARALLEL_ANT_COLONY_SYSTEM_PACO_H
#include "../sequential/model.h"
#include "pant.h"

class PACO: public Model{
public:
    PACO(int number_of_ants, double initial_alpha, double initial_beta, double initial_q,
         double initial_rho, Dataloader *p_dataloader);
    ~PACO();
    void construct_routes();
    void random_place_ants();
};


#endif //PARALLEL_ANT_COLONY_SYSTEM_PACO_H
