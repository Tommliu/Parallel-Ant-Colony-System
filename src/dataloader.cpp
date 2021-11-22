//
// Created by ZitengShu on 11/21/2021.
//
#include "dataloader.h"
#define UNUSED __attribute__((unused))
Dataloader::Dataloader() {
}

Dataloader::~Dataloader() {
    delete []cities;
    for (int i = 0; i < number_of_cities; i++) {
        delete [] distances[i];
    }
    delete [] distances;
}

double Dataloader::distance(int a_city, int b_city) {
    int delta_x = cities[a_city].x - cities[b_city].x;
    int delta_y = cities[a_city].y - cities[b_city].y;
    double delta_x_pow2 = static_cast<double>(delta_x * delta_x);
    double delta_y_pow2 = static_cast<double>(delta_y * delta_y);
    return std::sqrt(delta_x_pow2 + delta_y_pow2);
}

void Dataloader::load_data(const char *path) {
    FILE *tsp = fopen(path, "r");
    int UNUSED result;
    // Acquire number of cities from data set
    result = fscanf(tsp, "%d\n", &number_of_cities);
    cities = new city_t[number_of_cities];
    distances = new double*[number_of_cities];
    int tmp;
    for (int i = 0; i < number_of_cities; i++) {
        distances[i] = new double[number_of_cities];
        result = fscanf(tsp, "%d %d %d\n", &tmp, &(cities[i].x), &(cities[i].y));
    }
    // TODO: This part can be improved
    for (int i = 0; i < number_of_cities; i++) {
        for (int j = 0; j <= i; j++) {
            double dis_ij = distance(i, j);
            distances[i][j] = dis_ij;
            distances[j][i] = dis_ij;
        }
    }
}

void Dataloader::print_distances(int a, int b) {
    for (int i = 0; i <= a; i++) {
        for (int j = 0; j <= b; j++) {
            printf("%f\t", distances[i][j]);
        }
        printf("\n");
    }
}
