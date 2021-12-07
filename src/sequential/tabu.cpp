//
// Created by ZitengShu on 11/22/2021.
//

#include "tabu.h"
Tabu::Tabu() {
    list = nullptr;
    n_cities = -1;
}

Tabu::Tabu(int number_of_cities) {
    n_cities = number_of_cities;
    list = new char[number_of_cities];
    reset();
}

Tabu::~Tabu() {
    delete [] list;
}

Tabu::Tabu(const Tabu &tabu) {
    n_cities = tabu.n_cities;
    list = new char[n_cities];
    for (int i = 0; i < n_cities; ++i) {
        list[i] = tabu.list[i];
    }
}

void Tabu::init(int number_of_cities) {
    n_cities = number_of_cities;
    list = new char[number_of_cities];
    reset();
}

Tabu &Tabu::operator=(const Tabu &tabu) {
    n_cities = tabu.n_cities;
    if (!list) {
        list = new char[n_cities];
    }
    for (int i = 0; i < n_cities; ++i) {
        list[i] = tabu.list[i];
    }
    return *this;
}

void Tabu::reset() {
    for (int i = 0; i < n_cities; ++i) {
        list[i] = 0;
    }
}

char Tabu::is_visited(int city) {
    return list[city];
}