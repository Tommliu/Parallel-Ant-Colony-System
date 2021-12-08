//
// Created by ZitengShu on 12/8/2021.
//

#include "communicator.h"
Communicator::Communicator() {
    msg = nullptr;
}

Communicator::Communicator(size_t length) {
    length = msg_len;
    recv_buffer = new char[msg_len];
    send_buffer = new char[msg_len];
}

void Communicator::init(size_t length) {
    length = msg_len;
    recv_buffer = new char[msg_len];
    send_buffer = new char[msg_len];
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
    int *msg = (int *)send_buffer;
    int max_itr = solution.path.n_cities;
    for (int i = 0; i < max_itr; ++i) {
        msg[i] = solution.path.route[i];
    }
    double *plen = (double *)(send_buffer + length - sizeof(double));
    *plen = solution.length;
}

void Communicator::download_solution(Solution &solution) {
    int *msg = (int *)recv_buffer;
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