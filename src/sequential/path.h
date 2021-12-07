//
// Created by ZitengShu on 11/21/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_PATH_H
#define PARALLEL_ANT_COLONY_SYSTEM_PATH_H
#pragma once
#include "dataloader.h"
class Path {
public:
    Path();
    Path(int number_of_cities);
    Path(const Path &path);
    void init(int number_of_cities);
    Path& operator= (const Path&);
    virtual ~Path();
    void reset();
    double get_length(Dataloader *dataloader);

    int *route;         // Has N+1 node since there is N segments
    int n_cities;       // number of cities + 1
};
#endif //PARALLEL_ANT_COLONY_SYSTEM_PATH_H
