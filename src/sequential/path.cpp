//
// Created by ZitengShu on 11/21/2021.
//

#include "path.h"
Path::Path() {
    route = nullptr;
    n_cities = -1;
}

Path::Path(int number_of_cities) {
    n_cities = number_of_cities + 1;
    route = new int[n_cities];
    reset();
}

void Path::init(int number_of_cities) {
    n_cities = number_of_cities + 1;
    route = new int[n_cities];
    reset();
}

Path::~Path() {
    if (route) {
        delete [] route;
    }
}

Path::Path(const Path &path) {
    n_cities = path.n_cities;
    route = new int[n_cities];
    for (int i = 0; i < n_cities; ++i) {
        route[i] = path.route[i];
    }
}

Path &Path::operator= (const Path &path) {
    n_cities = path.n_cities;
    if (!route) {
        route = new int[n_cities];
    }
    for (int i = 0; i < n_cities; ++i) {
        route[i] = path.route[i];
    }
    return *this;
}

double Path::get_length(Dataloader *dataloader) {
    double sum = 0.0;
    for (int i = 1; i < n_cities; ++i) {
        sum += dataloader->distances[route[i-1]][route[i]];
    }
    return sum;
}

void Path::reset() {
    for (int i = 0; i < n_cities; ++i) {
        route[i] = -1;
    }
}