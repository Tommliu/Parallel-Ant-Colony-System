//
// Created by ZitengShu on 12/8/2021.
//

#include "topology.h"
Topology::Topology() {
    n_proc = 0;
}

void Topology::init(int number_of_processor) {
    n_proc = number_of_processor;
}

Topology::~Topology() {}

int Topology::ring_get_send(int rank) {
    return (rank + 1) % n_proc;
}

int Topology::ring_get_recv(int rank) {
    return (rank + n_proc - 1) % n_proc;
}