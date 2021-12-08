//
// Created by ZitengShu on 12/7/2021.
//

#include "paco.h"
PACO::PACO(int number_of_ants, double initial_alpha, double initial_beta,
           double initial_q, double initial_rho, Dataloader *p_dataloader): Model(number_of_ants, initial_alpha, initial_beta, initial_q, initial_rho, p_dataloader) {}
PACO::~PACO() {}

void PACO::random_place_ants() {
#pragma omp parallel for schedule(static)
    for (int i = 0; i < n_ants; ++i) {
        int city = random.get_initial_city(n_cities);
        ants[i].reset();
        ants[i].visit_city(0, city);
        ants[i].visit_city(n_cities, city);
    }
}


void PACO::construct_routes(Solution &local_best) {
#pragma omp declare reduction \
        (minLength:Solution:omp_out=better_solution(omp_out, omp_in)) \
        initializer(omp_priv = Solution())
    local_best.reset();
#pragma omp parallel for reduction(minLength: local_best)
    for (int i = 0; i < n_ants; ++i) {
        for (int j = 1; j < n_cities; ++j) {
            int next_city = random.get_next_city(&(ants[i]), (ants[i].path.route)[j-1],
                                                 n_cities, dataloader, pheromone, alpha, beta);
            ants[i].visit_city(j, next_city);
        }
        double length = ants[i].get_length(dataloader);
        Solution curr_solution(length, ants[i].path);

        local_best = better_solution(local_best, curr_solution);
    }

    if (local_best.length < global_best.length) {
        global_best = local_best;
    }
}