//
// Created by ZitengShu on 11/22/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_TABU_H
#define PARALLEL_ANT_COLONY_SYSTEM_TABU_H
#pragma once
#include <cstdio>

class Tabu {
public:
    Tabu();
    Tabu(int number_of_cities);
    Tabu(const Tabu& tabu);
    Tabu& operator= (const Tabu&);
    virtual ~Tabu();
    void init(int number_of_cities);

    char is_visited(int city);
    void reset();

    char *list;
    int n_cities;
};
#endif //PARALLEL_ANT_COLONY_SYSTEM_TABU_H
