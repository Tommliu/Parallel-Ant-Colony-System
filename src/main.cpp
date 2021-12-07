//
// Created by ZitengShu on 11/21/2021.
//
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "dataloader.h"
#include "model.h"
#define UNUSED __attribute__((unused))

int main(int argc, char *argv[]) {
    int UNUSED numIterations = 1;
    char *input_filename = NULL;
    double UNUSED alpha = 0.1;
    int opt = 0;

    int number_of_ants = 200, max_iteration = 200;
    double initial_alpha = 3.0, initial_beta = 4.0, initial_q = 100.0, initial_rho = 0.3;

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

            case 'i':
                numIterations = atoi(optarg);
                break;

            case -1:
                break;

            default:
                break;
        }
    } while (opt != -1);

    if (input_filename == NULL) {
        printf("Usage: %s -f <filename> [-a <Alpha>] [-i <N_iters>]\n", argv[0]);
        return -1;
    }
    Dataloader dataloader;
    dataloader.load_data(input_filename);

    // TODO: figure out initial parameters
    Model aco(number_of_ants, initial_alpha, initial_beta, initial_q, initial_rho, max_iteration, &dataloader);
    //printf("Building model\n");
    aco.solve(max_iteration);
    aco.write_output(input_filename);
    //printf("End write\n");
    return 0;
}