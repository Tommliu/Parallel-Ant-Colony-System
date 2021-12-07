//
// Created by ZitengShu on 11/21/2021.
//
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "sequential/dataloader.h"
#include "sequential/model.h"
#include "sequential/timer.h"
#define UNUSED __attribute__((unused))

int main(int argc, char *argv[]) {
    char *input_filename = NULL;
    int opt = 0;

    int number_of_ants = 200, max_iteration = 200;
    double alpha = 3.0, beta = 4.0, q = 100.0, rho = 0.3;
    int n_cores = 1;
    int UNUSED mode = 0;
    Model *model = nullptr;

    // Read command line arguments
    do {
        opt = getopt(argc, argv, "f:a:i:");
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
        printf("Usage: %s -f <filename> [-a <Alpha>] [-b <Beta>] [-q <Q>] [-r <Rho>] [-n <N_Ants>] [-i <N_Iterations>] [-c <N_Cores>]\n", argv[0]);
        return -1;
    }

    printf("[RUNNING]: %s with %d cores, (a, b, q, r, n, i) = (%f,%f,%f,%f,%d,%d)\n",
           input_filename, n_cores, alpha, beta, q, rho, number_of_ants, max_iteration);
    Timer timer;
    Dataloader dataloader;
    dataloader.load_data(input_filename);

    switch (mode) {
        case 0:
            model = new Model(number_of_ants, alpha, beta, q, rho, max_iteration, &dataloader);
            break;
        default:
            printf("[ERROR]: No specific mode!\n");
            exit(127);
    }

    timer.start();
    model->solve(max_iteration);
    timer.end();
    model->write_output(input_filename, n_cores, timer.get_duration_time());
    printf("[FINISH]: %s with %lf seconds\n", input_filename, timer.get_duration_time());
    return 0;
}