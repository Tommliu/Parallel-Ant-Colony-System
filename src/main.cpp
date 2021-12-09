//
// Created by ZitengShu on 11/21/2021.
//
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <omp.h>
#include "sequential/dataloader.h"
#include "sequential/model.h"
#include "sequential/timer.h"
#include "mpiaco/mpiaco.h"
#include "paco/paco.h"
#include "mulaco/mulaco.h"
#include <mpi.h>

#define UNUSED __attribute__((unused))

int main(int argc, char *argv[]) {
    char *input_filename = NULL;
    int opt = 0;

    int number_of_ants = 200, max_iteration = 200;
    double alpha = 3.0, beta = 4.0, q = 100.0, rho = 0.3;
    int n_cores = 1;
    int mode = 0;
    Model *model = nullptr;

    // Read command line arguments
    do {
        opt = getopt(argc, argv, "f:a:b:q:r:n:i:c:m:");
        switch (opt) {
            case 'f':
                input_filename = optarg;
                break;
            case 'a':
                alpha = atof(optarg);
                break;
            case 'b':
                beta = atof(optarg);
                break;
            case 'q':
                q = atof(optarg);
                break;
            case 'r':
                rho = atof(optarg);
                break;
            case 'n':
                number_of_ants = atoi(optarg);
                break;
            case 'i':
                max_iteration = atoi(optarg);
                break;
            case 'c':
                n_cores = atoi(optarg);
                break;
            case 'm':
                mode = atoi(optarg);
                break;
            case -1:
                break;
            default:
                break;
        }
    } while (opt != -1);

    if (input_filename == NULL) {
        printf("Usage: %s -f <filename> [-a <Alpha>] [-b <Beta>] [-q <Q>] [-r <Rho>] [-n <N_Ants>] [-i <N_Iterations>] [-c <N_Cores>] [-m <ACO_Model>]\n", argv[0]);
        return -1;
    }

    Dataloader dataloader;
    dataloader.load_data(input_filename);

    int proc_id;
    switch (mode) {
        case 0:
            model = new Model(number_of_ants, alpha, beta, q, rho, &dataloader);
            break;
        case 1:
            omp_set_num_threads(n_cores);
            model = new PACO(number_of_ants, alpha, beta, q, rho, &dataloader);
            break;
        case 2:
           MPI_Init(&argc, &argv);
           MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
           MPI_Comm_size(MPI_COMM_WORLD, &n_cores);
           model = new MPIACO(number_of_ants, proc_id, n_cores, alpha, beta, q, rho, max_iteration, &dataloader);
           break;
        case 3:
            MPI_Init(NULL, NULL);
            MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
            MPI_Comm_size(MPI_COMM_WORLD, &n_cores);
            model = new MulACO(number_of_ants, alpha, beta, q, rho, &dataloader, proc_id, n_cores);
            break;
        default:
            printf("[ERROR]: No specific mode %d!\n", mode);
            exit(127);
    }

    printf("[RUNNING]: %s using mode %d with %d cores, (a, b, q, r, n, i) = (%f,%f,%f,%f,%d,%d)\n",
           input_filename, mode, n_cores, alpha, beta, q, rho, number_of_ants, max_iteration);
    Timer timer;
    timer.start();
    model->solve(max_iteration);
    timer.end();


    switch (mode) {
        case 0:
        case 1:
            model->write_output(input_filename, n_cores, timer.get_duration_time(), mode);
            printf("[FINISH]: %s with %lf seconds\n", input_filename, timer.get_duration_time());
            delete model;
            break;
        case 2:
        case 3:
            if (proc_id == 0) {
                model->write_output(input_filename, n_cores, timer.get_duration_time(), mode);
                printf("[FINISH]: %s with %lf seconds\n", input_filename, timer.get_duration_time());
            }
            delete model;
            MPI_Finalize();
            break;
        default:
            printf("[ERROR]: No specific mode!\n");
            exit(127);
    }
    return 0;
}