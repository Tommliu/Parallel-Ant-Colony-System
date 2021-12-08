//
// Created by ZitengShu on 12/7/2021.
//

#include "solution.h"
Solution::Solution() {
    length = static_cast<double>(INT_MAX);
}

Solution::Solution(double len, Path &p) {
    length = len;
    path = p;
}

Solution::~Solution() {}

Solution::Solution(const Solution &solution) {
    length = solution.length;
    path = solution.path;
}

Solution &Solution::operator=(const Solution &solution) {
    length = solution.length;
    path = solution.path;
    return *this;
}

void Solution::update_pheromone(double **phero, double Q, Dataloader *dataloader) {
    int max_itr = path.n_cities;
    for (int i = 1; i < max_itr; ++i) {
        int start = path.route[i-1];
        int end = path.route[i];
        phero[start][end] +=  Q / length;
        phero[end][start] = phero[start][end];
    }
}

void Solution::reset() {
    length = static_cast<double>(INT_MAX);
}

bool Solution::operator< (Solution& solution) {
    if (length < solution.length) { return true; }
    else { return false; }
}