//
// Created by ZitengShu on 12/8/2021.
//

#include "communicator.h"
Communicator::Communicator() {
    recv_buffer = nullptr;
    send_buffer = nullptr;
}

void Communicator::init(size_t msg_length, int number_of_cities) {
    length = msg_length;
    n_cities = number_of_cities + 1;
    recv_buffer = new char[length];
    send_buffer = new char[length];
}

Communicator::~Communicator() {
    delete [] recv_buffer;
    delete [] send_buffer;
}

void Communicator::send_msg(int destination, int tag) {
    MPI_Send(send_buffer, length, MPI_BYTE, destination, tag, MPI_COMM_WORLD);
}

char *Communicator::receive_msg(int source, int tag) {
    MPI_Recv(recv_buffer, length, MPI_BYTE, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void Communicator::upload_solution(Solution &solution) {
    solution.init();
    int *msg = (int *)send_buffer;
    for (int i = 0; i < n_cities; ++i) {
        msg[i] = solution.path.route[i];
    }
    double *plen = (double *)(send_buffer + length - sizeof(double));
    *plen = solution.length;
}

void Communicator::download_solution(Solution &solution) {
    solution.init();
    int *msg = (int *)recv_buffer;
    for (int i = 0; i < n_cities; ++i) {
        solution.path.route[i] = msg[i];
    }
    double *plen = (double *)(recv_buffer + length - sizeof(double));
    solution.length = *plen;
}

void Communicator::download_from_broadcast(Solution &solution) {
    solution.init();
    int *msg = (int *)send_buffer;
    int max_itr = solution.path.n_cities;
    for (int i = 0; i < max_itr; ++i) {
        solution.path.route[i] = msg[i];
    }
    double *plen = (double *)(send_buffer + length - sizeof(double));
    solution.length = *plen;
}

void Communicator::broadcast_msg(int root) {
    MPI_Bcast(send_buffer, length, MPI_BYTE, root, MPI_COMM_WORLD);
}

char *Communicator::get_recv_buffer() {
    return recv_buffer;
}

char *Communicator::get_send_buffer() {
    return send_buffer;
}