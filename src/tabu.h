//
// Created by ZitengShu on 11/22/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_TABU_H
#define PARALLEL_ANT_COLONY_SYSTEM_TABU_H
#pragma once

class Tabu {
public:
    Tabu(int number_of_cities);
    virtual ~Tabu();
    bool is_visited(int city);
    void reset();

    bool *list;
    int n_cities;
};
#endif //PARALLEL_ANT_COLONY_SYSTEM_TABU_H
