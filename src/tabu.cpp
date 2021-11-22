//
// Created by ZitengShu on 11/22/2021.
//

#include "tabu.h"
Tabu::Tabu(int number_of_cities) {
    n_cities = number_of_cities;
    list = new bool[n_cities];
    reset();
}

Tabu::~Tabu() {
    delete [] list;
}

void Tabu::reset() {
    for (int i = 0; i < n_cities; ++i) {
        list[i] = false;
    }
}

bool Tabu::is_visited(int city) {
    return list[city];
}