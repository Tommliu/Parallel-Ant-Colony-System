//
// Created by ZitengShu on 11/20/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_DATALOADER_H
#define PARALLEL_ANT_COLONY_SYSTEM_DATALOADER_H
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

typedef struct city_position {
    int x, y;
}city_t;


class Dataloader {
public:
    Dataloader();
    virtual ~Dataloader();
    double distance(int a_city, int b_city);
    void load_data(const char *path);

    int n_cities;
    double **distances;     // N^2
    city_t *cities;     // N
};
#endif //PARALLEL_ANT_COLONY_SYSTEM_DATALOADER_H
