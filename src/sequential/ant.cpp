//
// Created by ZitengShu on 11/21/2021.
//

#include "ant.h"
Ant::Ant() {}

void Ant::initialize(int number_of_cities) {
    path.init(number_of_cities);
    tabu_list.init(number_of_cities);
    probe = new double[number_of_cities];
    for (int i = 0; i < number_of_cities; ++i) {
        probe[i] = 0.0;
    }
    N = number_of_cities;
}

void Ant::release() {
    delete [] probe;
}

Ant::~Ant() {}

void Ant::visit_city(int index, int city) {
    path.route[index] = city;
    tabu_list.list[city] = 1;
}

double Ant::get_length(Dataloader *dataloader) {
    return path.get_length(dataloader);
}

int Ant::get_phero_loc(int i, int j) {
    if (i == j) {
        printf("[ERROR]: ant:get_phero_loc(%d,%d)\n", i, j);
        return -1;
    }
    int x, y;
    if (i < j) {
        x = i;
        y = j;
    } else {
        x = j;
        y = i;
    }
    return (2 * N - 3 - x) * x / 2 + y - x;
}

void Ant::update_probe(int start, int n_cities, Dataloader *dataloader,
                       double *phero, double alpha, double beta) {
    double sum = 0.0;
    for (int i = 0; i < n_cities; ++i) {
        if (tabu_list.is_visited(i)) {
            probe[i] = 0;
       } else {
            double dis = (dataloader->distances)[start][i];
            int loc = get_phero_loc(start, i);
            double ph = phero[loc];
            double dis_inv = 1.0 / dis;
            double ETA = pow(dis_inv, beta);
            double TAU = pow(ph, alpha);
            if (ETA == 0.0) {
                printf("[ERROR]:ETA too small\n");
            }
            double prob_si = ETA * TAU;

            probe[i] = prob_si;
            sum += prob_si;

       }
    }
    if (sum == 0.0) {
        perror("[ERROR]: Failed to update probe!\n");
    }
    for (int i = 0; i < n_cities; ++i) {
        probe[i] /= sum;
    }
}

void Ant::reset() {
    path.reset();
    tabu_list.reset();
}