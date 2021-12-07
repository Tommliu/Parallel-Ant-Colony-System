//
// Created by ZitengShu on 12/7/2021.
//

#include "solution.h"
Solution::Solution() {
    length = static_cast<double>(INT_MAX);
    iant = -1;
}

Solution::Solution(double len, int ant, Path &p) {
    length = len;
    path = p;
    iant = ant;

}

Solution::~Solution() {}

Solution::Solution(const Solution &solution) {
    length = solution.length;
    path = solution.path;
    iant = solution.iant;
}

Solution &Solution::operator=(const Solution &solution) {
    length = solution.length;
    path = solution.path;
    iant = solution.iant;
    return *this;
}

void Solution::rest() {
    length = static_cast<double>(INT_MAX);
    iant = -1;
}