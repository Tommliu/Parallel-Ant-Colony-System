//
// Created by ZitengShu on 11/21/2021.
//

#include "random.h"
Random::Random() {}
Random::~Random() {}

int Random::get_initial_city(int n_cities) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int> distribution(0, n_cities - 1);
    return distribution(gen);
}

// TODO: generate next city base on the tabu list
int Random::get_next_city(Ant *ant, int start, int n_cities, Dataloader *dataloader,
                          double **phero, double alpha, double beta) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    ant->update_probe(start, n_cities, dataloader, phero, alpha, beta);
    double p = distribution(gen);
    int i;
    for (i = 0; i < n_cities; ++i) {
        if (ant->probe[i] > 0 && ant->probe[i] <= p) {
            break;
        }
    }

    return i;
}