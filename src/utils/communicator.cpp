//
// Created by ZitengShu on 12/8/2021.
//

#include "communicator.h"
Communicator::Communicator() {
    msg = nullptr;
}

Communicator::Communicator(int length) {
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

void Communicator::broadcast_msg(int root) {
    MPI_Bcast(send_buffer, length, MPI_BYTE, root, MPI_COMM_WORLD);
}

char *Communicator::get_recv_buffer() {
    return recv_buffer;
}

char *Communicator::get_send_buffer() {
    return send_buffer;
}