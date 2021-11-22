//
// Created by ZitengShu on 11/21/2021.
//
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "dataloader.h"
#define UNUSED __attribute__((unused))

int main(int argc, char *argv[]) {
    int UNUSED numIterations = 5;
    char *input_filename = NULL;
    double UNUSED alpha = 0.1;
    int opt = 0;

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
    

}