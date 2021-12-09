//
// Created by ZitengShu on 12/8/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_TOPOLOGY_H
#define PARALLEL_ANT_COLONY_SYSTEM_TOPOLOGY_H

class Topology {
public:
    Topology();
    void init(int number_of_processor);
    ~Topology();
    int ring_get_send(int rank);
    int ring_get_recv(int rank);
    int n_proc;
};


#endif //PARALLEL_ANT_COLONY_SYSTEM_TOPOLOGY_H
