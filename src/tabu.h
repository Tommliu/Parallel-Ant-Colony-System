//
// Created by ZitengShu on 11/22/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_TABU_H
#define PARALLEL_ANT_COLONY_SYSTEM_TABU_H
#pragma once
#include <cstdio>

class Tabu {
public:
    Tabu(int number_of_cities);
    virtual ~Tabu();
    char is_visited(int city);
    void reset();

    char *list;
    int n_cities;
};
#endif //PARALLEL_ANT_COLONY_SYSTEM_TABU_H
