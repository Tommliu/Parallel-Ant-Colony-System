//
// Created by ZitengShu on 12/7/2021.
//

#include "pant.h"
pAnt::pAnt(): Ant() {}
pAnt::~pAnt() {}

void pAnt::update_pheromone(double **phero, double Q, Dataloader *dataloader) {
    double length = path.get_length(dataloader);
    int max_itr = path.n_cities;

#pragma omp parallel for schedule(static)
    for (int i = 1; i < max_itr; ++i) {
        int start = path.route[i-1];
        int end = path.route[i];
        phero[start][end] +=  Q / length;
        phero[end][start] = phero[start][end];
    }
}