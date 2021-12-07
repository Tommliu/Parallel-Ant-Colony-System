//
// Created by ZitengShu on 12/7/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_PANT_H
#define PARALLEL_ANT_COLONY_SYSTEM_PANT_H
#include "../sequential/ant.h"

class pAnt: public Ant{
public:
    pAnt();
    ~pAnt();
    void update_pheromone(double **phero, double Q, Dataloader *dataloader);
};


#endif //PARALLEL_ANT_COLONY_SYSTEM_PANT_H
