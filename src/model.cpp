//
// Created by ZitengShu on 11/21/2021.
//

#include "model.h"
#define UNUSED __attribute__((unused))
Model::Model(int number_of_ants, double initial_alpha, double initial_beta, double initial_q,
             double initial_rho, int initial_city, Dataloader *p_dataloader) {
    n_ants = number_of_ants;
    n_cities = p_dataloader->n_cities;
    alpha = initial_alpha;
    beta = initial_beta;
    q = initial_q;
    rho = initial_rho;
    decay_rate = 1.0 - rho;

    dataloader = p_dataloader;

    random = new Random();
    ants = new Ant[n_ants];
    pheromone = new double* [n_cities];
    best_route = new Path(n_cities);
    best_ant = -1;

    for (int i = 0; i < n_cities; i++) {
        pheromone[i] = new double [n_cities];

        best_route->route[i] = -1;
        for (int j = 0; j < n_cities; j++) {
            // TODO: initialization
            pheromone[i][j] = 1.0;
        }
    }
    for (int i = 0; i < n_ants; ++i) {
        ants[i].initialize(n_cities);
    }

    local_best_length = static_cast<double>(INT_MAX);
    global_best_length = local_best_length;
}

Model::~Model() {
    for (int i = 0; i < n_cities; i++) {
        delete [] pheromone[i];
    }
    delete [] pheromone;

    delete best_route;
    delete random;
    for (int i = 0; i < n_ants; ++i) {
        ants[i].release();
    }
    delete [] ants;
}

void Model::random_place_ants() {
    for (int i = 0; i < n_ants; ++i) {
        int city = random->get_initial_city(n_cities);
        ants[i].reset();
        ants[i].visit_city(0, city);
        ants[i].visit_city(n_cities, city);
    }
}

void Model::construct_routes() {
    for (int i = 0; i < n_ants; ++i) {
        for (int j = 1; j < n_cities; ++j) {
            int next_city = random->get_next_city(&(ants[i]), (ants[i].path->route)[j-1],
                                                  n_cities, dataloader, pheromone, alpha, beta);
            ants[i].visit_city(j, next_city);
        }
        double length = ants[i].get_length(dataloader);
        if (length < local_best_length) {
            local_best_length = length;
            best_route->copy(ants[i].path);
            best_ant = i;
        }
    }
    if (local_best_length < global_best_length) {
        global_best_length = local_best_length;
        best_route->copy(ants[best_ant].path);
    }
    local_best_length = static_cast<double>(INT_MAX);
}

void Model::pheromone_decay() {
    for (int i = 0; i < n_cities; ++i) {
        for (int j = 0; j < n_cities; ++j) {
            pheromone[i][j] *= decay_rate;
        }
    }
}

// Only update the best ant's path
void Model::update_pheromone() {
    pheromone_decay();
    ants[best_ant].update_pheromone(pheromone, q, dataloader);
}

void Model::solve(int max_iter) {
    for (int i = 0; i < max_iter; ++i) {
        random_place_ants();
        // update best route
        construct_routes();
        update_pheromone();
    }
}

void Model::write_output(const char* UNUSED input_path) {
    int result = access("./output", F_OK);
    if (result) {
        int res = mkdir("./output", 0755);
        if (res) {
            printf("[ERROR]: Create directory %d\n", errno);
        }
    }

    FILE *fp0 = fopen("./output/xqf131_profile", "a");
    if (fp0 == NULL) {
        printf("[ERROR]:failed to open output profile file\n");
    }
    // fprintf(fp, "DATASET: VLSI\n");
    fprintf(fp0, "TOUR LENGTH: %f\n", global_best_length);
    fprintf(fp0, "COMPUTATION TIME: 10\n");

    FILE *fp = fopen("./output/xqf131_4", "w");
    if (fp == NULL) {
        printf("[ERROR]:failed to open output file\n");
    }
    fprintf(fp, "NAME: xqf131\n");
    fprintf(fp, "DIMENSION: %d\n", n_cities);
    int max_itr = n_cities + 1;
    for (int i = 0; i < max_itr; ++i) {
        int city = best_route->route[i];
        city_t tmp = (dataloader->cities)[city];
        fprintf(fp, "%d %d\n", tmp.x, tmp.y);
    }
    fclose(fp);
}