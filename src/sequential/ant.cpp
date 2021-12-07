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


void Ant::update_probe(int start, int n_cities, Dataloader *dataloader,
                       double **phero, double alpha, double beta) {
    double sum = 0.0;
    for (int i = 0; i < n_cities; ++i) {
        if (tabu_list.is_visited(i)) {
            probe[i] = 0;
       } else {
            double dis = (dataloader->distances)[start][i];
            //printf("(%d, %d) = %f\n", start, i, dis);

            double ph = phero[start][i];

            double dis_inv = 1.0 / dis;
            double ETA = pow(dis_inv, beta);

            double TAU = pow(ph, alpha);
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

void Ant::update_pheromone(double **phero, double Q, Dataloader *dataloader) {
    double length = path.get_length(dataloader);
    int max_itr = path.n_cities;
    for (int i = 1; i < max_itr; ++i) {
        int start = path.route[i-1];
        int end = path.route[i];
        phero[start][end] +=  Q / length;
        phero[end][start] = phero[start][end];
    }
}

void Ant::reset() {
    path.reset();
    tabu_list.reset();
}