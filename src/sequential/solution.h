//
// Created by ZitengShu on 12/7/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_SOLUTION_H
#define PARALLEL_ANT_COLONY_SYSTEM_SOLUTION_H
#pragma once
#include "path.h"
#include <climits>

class Solution {
public:
    Solution();
    Solution(double len, int ant, Path& p);
    Solution(const Solution &solution);
    Solution& operator= (const Solution& solution);
    bool operator< (Solution& solution);
    virtual ~Solution();
    void reset();
    double length;
    Path path;
    int iant;
};


#endif //PARALLEL_ANT_COLONY_SYSTEM_SOLUTION_H
