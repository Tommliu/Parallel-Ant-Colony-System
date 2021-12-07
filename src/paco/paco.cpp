//
// Created by ZitengShu on 12/7/2021.
//

#include "paco.h"
PACO::PACO(int number_of_ants, double initial_alpha, double initial_beta, double initial_q, double initial_rho, int max_iteration, Dataloader *p_dataloader): Model(number_of_ants, initial_alpha, initial_beta, initial_q, initial_rho, max_iteration, p_dataloader) {}

PACO::~PACO(){}

Solution& myMin(Solution& x, Solution& y) {
    return x < y ? x : y;
}

void PACO::construct_routes() {

#pragma omp declare reduction \
        (minLength:Solution:omp_out=myMin(omp_out, omp_in)) \
        initializer(omp_priv = Solution())

#pragma omp parallel for reduction(minLength: local_best)
    for (int i = 0; i < n_ants; ++i) {
        for (int j = 1; j < n_cities; ++j) {
            int next_city = random.get_next_city(&(ants[i]), (ants[i].path.route)[j-1],
                                                 n_cities, dataloader, pheromone, alpha, beta);
            ants[i].visit_city(j, next_city);
        }
        double length = ants[i].get_length(dataloader);

        Solution curr_solution(length, i, ants[i].path);

        local_best = myMin(local_best, curr_solution);

    }

    if (local_best.length < global_best.length) {
        global_best = local_best;
    }
    local_best.reset();
}