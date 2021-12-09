//
// Created by ZitengShu on 12/8/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_COMMUNICATOR_H
#define PARALLEL_ANT_COLONY_SYSTEM_COMMUNICATOR_H
#include "../sequential/solution.h"
#include "mpi.h"

class Communicator {
public:
    Communicator();
    ~Communicator();

    void init(size_t length, int number_of_cities);

    void send_msg(int destination, int tag);
    void receive_msg(int source, int tag);
    void broadcast_msg(int root);
    void upload_solution(Solution &solution);
    void download_solution(Solution &solution);
    void download_from_broadcast(Solution &solution);
    char *get_send_buffer();
    char *get_recv_buffer();


    char *recv_buffer, *send_buffer;
    size_t length;
    int n_cities;
};


#endif //PARALLEL_ANT_COLONY_SYSTEM_COMMUNICATOR_H
