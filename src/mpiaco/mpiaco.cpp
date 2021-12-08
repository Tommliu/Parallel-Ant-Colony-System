#include "mpiaco.h"


using namespace::std;


MPIACO::MPIACO(int number_of_ants, int procID, int nproc, double initial_alpha, double initial_beta, double initial_q, \
        double initial_rho, int max_iteration, Dataloader *p_dataloader) {
    init(initial_alpha, initial_beta, initial_q, initial_rho, p_dataloader);
    int my_ants = init_ants(number_of_ants, procID, nproc);
    ants = new Ant[my_ants];
    sync_data = (char *)malloc(sizeof(Solution));
    myrank_ = procID;
    nproc_ = nproc;

    for (int i = 0; i < n_ants; ++i) {
        ants[i].initialize(n_cities);
    }
}

MPIACO::~MPIACO(){
    free(sync_data);
}


int MPIACO::init_ants(int procID, int nproc, int number_of_ants) {
    int group_size = number_of_ants / nproc;
    if (procID == nproc - 1) {
        group_size += number_of_ants % group_size;
    }
    return group_size;
}   


void MPIACO::update_pheromone(){
    size_t soln_size = sizeof(local_best);
    Solution *best_soln_sync;
    Solution best_soln = local_best;
    memcpy(sync_data, &local_best, soln_size);
    if (myrank_ == 0) {
        Solution *recv_soln;
        for (int i = 1; i < nproc_; i++) {
            MPI_Recv(sync_data, soln_size, MPI_BYTE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            recv_soln = reinterpret_cast<Solution *>(sync_data);
            if (*recv_soln <  best_soln) {
                best_soln = *recv_soln;
                memcpy(sync_data, recv_soln, soln_size);
            }
        }
    } else {
        MPI_Send(sync_data, soln_size, MPI_BYTE, 0, 0, MPI_COMM_WORLD); //to proc 0
    }

    // Broadcast the best solution across processors
    MPI_Bcast(sync_data, soln_size, MPI_BYTE, 0, MPI_COMM_WORLD); // broadcast the best path
    best_soln_sync = reinterpret_cast<Solution *>(sync_data);
    best_soln_sync->update_pheromone(pheromone, q, dataloader);
    if (*best_soln_sync < global_best) {
        global_best = *best_soln_sync;
    }
}

