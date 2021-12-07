//
// Created by ZitengShu on 12/7/2021.
//

#include "paco.h"
PACO::PACO(int number_of_ants, double initial_alpha, double initial_beta, double initial_q, double initial_rho, int max_iteration, Dataloader *p_dataloader): Model(number_of_ants, initial_alpha, initial_beta, initial_q, initial_rho, max_iteration, p_dataloader) {}

PACO::~PACO(){}

void PACO::construct_routes() {
    /**
#pragma omp declare reduction \
        (minIndex:int4:omp_out=myMin(omp_out, omp_in)) \
        initializer(omp_priv = int4(100000000, 100000000, 0, 0))

#pragma omp parallel for reduction(minIndex: min_value_index)
    for (int i = 0; i < n_ants; ++i) {
        for (int j = 1; j < n_cities; ++j) {
            int next_city = random->get_next_city(&(ants[i]), (ants[i].path->route)[j-1],
                                                  n_cities, dataloader, pheromone, alpha, beta);
            ants[i].visit_city(j, next_city);
        }
        double length = ants[i].get_length(dataloader);
        if (length < local_best_length) {
            local_best_length = length;
            best_route = ants[i].path;
            best_ant = i;
        }
    }
    if (local_best_length < global_best_length) {
        global_best_length = local_best_length;
        best_route = ants[best_ant].path;
    }
    local_best_length = static_cast<double>(INT_MAX);
     */
}