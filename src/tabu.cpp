//
// Created by ZitengShu on 11/22/2021.
//

#include "tabu.h"
Tabu::Tabu(int number_of_cities) {
    n_cities = number_of_cities;
    list = new char[number_of_cities];
    reset();
}

Tabu::~Tabu() {
    //printf("[DEBUG]: Start Tabu\n");

    delete [] list;
    //printf("[DEBUG]: End Tabu\n");
}

void Tabu::reset() {
    for (int i = 0; i < n_cities; ++i) {
        list[i] = 0;
    }
}

char Tabu::is_visited(int city) {
    return list[city];
}