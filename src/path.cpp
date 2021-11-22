//
// Created by ZitengShu on 11/21/2021.
//

#include "path.h"
Path::Path(int number_of_cities) {
    route = new int[number_of_cities];
    n_cities = number_of_cities;
    reset();
}

Path::~Path() {
    delete [] route;
}

Path &Path::operator=(const Path &other) {
    if (this == &other) {
        return *this;
    }
    delete [] route;
    route = new int[n_cities];
    for (int i = 0; i < n_cities; ++i) {
        route[i] = other.route[i];
    }
    return *this;
}

double Path::get_length(Dataloader *dataloader) {
    double sum = 0.0;
    int max_itr = n_cities - 1;
    for (int i = 0; i < max_itr; ++i) {
        sum += dataloader->distances[route[i]][route[i+1]];
    }
    sum += dataloader->distances[route[0]][route[max_itr]];
    return sum;
}

void Path::reset() {
    for (int i = 0; i < n_cities; ++i) {
        route[i] = -1;
    }
}