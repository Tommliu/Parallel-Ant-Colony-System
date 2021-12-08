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

void Solution::init(int number_of_cities) {
    if (path.route) {
        path.n_cities = number_of_cities;
        path.route = new int[path.n_cities];
    }
}
void Solution::reset() {
    length = static_cast<double>(INT_MAX);
}

bool Solution::operator< (Solution& solution) {
    if (length < solution.length) { return true; }
    else { return false; }
}