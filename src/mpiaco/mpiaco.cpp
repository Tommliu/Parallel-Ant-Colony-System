#include "mpiaco.h"


using namespace::std;


MPIACO::MPIACO(int number_of_ants, int procID, int nproc, double initial_alpha, double initial_beta, double initial_q, \
        double initial_rho, int max_iteration, Dataloader *p_dataloader) : Model(number_of_ants, initial_alpha, \
        initial_beta, initial_q, initial_rho, p_dataloader) {
    init_comm(dataloader);
    myrank = procID;
    nproc_ = nproc;
}

MPIACO::~MPIACO(){}

void MPIACO::init_comm(Dataloader *p_dataloader) {
    int n_cites = p_dataloader->n_cities;
    int length = n_cites + 1;
    size_t msg_length = length * sizeof(int) + sizeof(double);  // (int[n_cites + 1], double)
    comm.init(msg_length, n_cites);
}


void MPIACO::update_pheromone(Solution &local_best) {
    Solution best_soln = local_best;
    if (myrank == 0) {
        Solution recv_soln;
        recv_soln.init(n_cities + 1);
        for (int i = 1; i < nproc_; i++) {
            comm.receive_msg(i, 0);
            comm.download_solution(recv_soln);
            if (recv_soln <  best_soln) {
                best_soln = recv_soln;
            }
        }
        comm.upload_solution(best_soln);
    } else {
        comm.upload_solution(local_best);  // proc 0
        comm.send_msg(0, 0);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    comm.broadcast_msg(0);       // broadcast the best path
    comm.download_from_broadcast(best_soln);

    if (best_soln < global_best) {
        global_best = best_soln;
    }
    
    Model::update_pheromone(best_soln);
}

