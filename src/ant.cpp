//
// Created by ZitengShu on 11/21/2021.
//

#include "ant.h"
Ant::Ant(int number_of_cities) {
    path = new Path(number_of_cities);
    tabu_list = new Tabu(number_of_cities);
    probe = new double[number_of_cities];
}

Ant::~Ant() {
    delete path;
    delete tabu_list;
    delete probe;
}

void Ant::visit_city(int index, int city) {
    path->route[index] = city;
    tabu_list->list[city] = true;
}

double Ant::get_length(Dataloader *dataloader) {
    return path->get_length(dataloader);
}

void Ant::update_probe(int start, int n_cities, Dataloader *dataloader,
                       double **phero, double alpha, double beta) {
    double sum = 0.0;
    for (int i = 0; i < n_cities; ++i) {
       if (tabu_list->is_visited(start)) {
            probe[i] = 0;
       } else {
           double ETA = (double) pow(1.0/dataloader->distances[start][i], beta);
           double TAU = (double) pow(phero[start][i], alpha);
           double prob_si = ETA * TAU;
           probe[i] = prob_si;
           sum += prob_si;
       }
    }
    for (int i = 0; i < n_cities; ++i) {
        probe[i] /= sum;
    }
}

void Ant::update_pheromone(double **phero, double Q, Dataloader *dataloader) {
    double length = path->get_length(dataloader);
    int max_itr = path->n_cities - 1;
    for (int i = 0; i < max_itr; ++i) {
        int start = path->route[i];
        int end = path->route[i+1];
        phero[start][end] +=  Q / length;
        phero[end][start] = phero[start][end];
    }
}

void Ant::reset() {
    path->reset();
    tabu_list->reset();
}