//
// Created by ZitengShu on 12/8/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_MULACO_H
#define PARALLEL_ANT_COLONY_SYSTEM_MULACO_H
#include "../sequential/model.h"
#include "../utils/communicator.h"

class MulACO: public Model{
    MulACO();
    ~MulACO();

    Communicator communicator;
};


#endif //PARALLEL_ANT_COLONY_SYSTEM_MULACO_H
