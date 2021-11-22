//
// Created by ZitengShu on 11/21/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_PATH_H
#define PARALLEL_ANT_COLONY_SYSTEM_PATH_H
#pragma once
#include "dataloader.h"
class Path {
public:
    Path(int number_of_cities);
    virtual ~Path();
    Path& operator=(const Path& route);
    void reset();
    double get_length(Dataloader *dataloader);

    int *route;
    int n_cities;
};
#endif //PARALLEL_ANT_COLONY_SYSTEM_PATH_H
