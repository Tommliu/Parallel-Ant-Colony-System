//
// Created by ZitengShu on 12/8/2021.
//

#include "mulaco.h"
MulACO::MulACO(int number_of_ants, double initial_alpha, double initial_beta, double initial_q, double initial_rho, Dataloader *p_dataloader, int proc_id, int number_of_proc) : Model(number_of_ants, initial_alpha, initial_beta, initial_q, initial_rho, p_dataloader) {
    size_t msg_length = (n_cities + 1) * sizeof(int) + sizeof(double);
    communicator.init(msg_length, n_cities);
    rank = proc_id;
    ring.init(number_of_proc);
    nproc = number_of_proc;
}
MulACO::~MulACO(){}

void MulACO::solve(int max_itr) {
    Solution local_best;
    int cnt = 1;
    for (int i = 0; i < max_itr; ++i, ++cnt) {
        random_place_ants();
        // update best route
        construct_routes(local_best);
        communication(local_best);
        update_pheromone(local_best);
    }
    collect_global_best();
}

void MulACO::communication(Solution &local_best) {
    int source = ring.ring_get_recv(rank);
    int target = ring.ring_get_send(rank);
    if (rank != 0) {
        communicator.receive_msg(source, 0);
    }
    communicator.upload_solution(local_best);
    communicator.send_msg(target, 0);

    if (rank == 0) {
        communicator.receive_msg(source, 0);
    }
    Solution comm_solution;
    communicator.download_solution(comm_solution);
    local_best = better_solution(local_best, comm_solution);
}

void MulACO::collect_global_best() {
    if (rank == 0) {
        for (int i = 1; i < nproc; ++i) {
            communicator.receive_msg(i, 0);
            Solution comm_sol;
            communicator.download_solution(comm_sol);
            global_best = better_solution(global_best, comm_sol);
        }
    }
    communicator.upload_solution(global_best);
    communicator.send_msg(0, 0);
}