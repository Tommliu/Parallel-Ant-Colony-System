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
    ants = std::vector<Ant>(n_ants, Ant(n_cities));
    pheromone = new double* [n_cities];
    best_route = new Path(n_cities);

    for (int i = 0; i < n_cities; i++) {
        pheromone[i] = new double [n_cities];

        best_route->route[i] = -1;
        for (int j = 0; j < n_cities; j++) {
            // TODO: initialization
            pheromone[i][j] = 1.0;
        }
    }

    best_length = static_cast<double>(INT_MAX);
}

Model::~Model() {
    //printf("[DEBUG]: Start Model\n");

    for (int i = 0; i < n_cities; i++) {
        delete [] pheromone[i];
    }
    delete [] pheromone;

    delete best_route;
    delete random;
    //printf("[DEBUG]: End model\n");
}

void Model::random_place_ants() {
    for (int i = 0; i < n_ants; ++i) {
        int city = random->get_initial_city(n_cities);
        ants[i].reset();
        ants[i].visit_city(0, city);
        printf("Ant %d, start citiy %d\n", i, city);
    }
}

void Model::construct_routes() {
    //printf("construct_routes, (%d, %d)\n", n_ants, n_cities);
    for (int i = 0; i < n_ants; ++i) {
        for (int j = 1; j < n_cities; ++j) {
            int next_city = random->get_next_city(&(ants[i]), (ants[i].path->route)[j-1],
                                                  n_cities, dataloader, pheromone, alpha, beta);
            //printf("next %d\n", next_city);
            ants[i].visit_city(j, next_city);
        }
        double length = ants[i].get_length(dataloader);
        if (length < best_length) {
            best_length = length;
            best_route->copy(ants[i].path);
        }
    }
}

void Model::pheromone_decay() {
    for (int i = 0; i < n_cities; ++i) {
        for (int j = 0; j < n_cities; ++j) {
            pheromone[i][j] *= decay_rate;
        }
    }
}

void Model::update_pheromone() {
    pheromone_decay();
    for (int i = 0; i < n_ants; ++i) {
        ants[i].update_pheromone(pheromone, q, dataloader);
    }
}

void Model::solve(int max_iter) {
    printf("Call solve\n");

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
    FILE *fp = fopen("./output/vlsi_output.tsp", "w");
    if (fp == nullptr) {
        printf("[ERROR]:failed to open output file\n");
    }
    fprintf(fp, "NAME: xqf131\n");
    fprintf(fp, "DATASET: VLSI\n");
    fprintf(fp, "TOUR LENGTH: %f\n", best_length);
    fprintf(fp, "COMPUTATION TIME: 10\n");
    fprintf(fp, "DIMENSION: %d\n", n_cities);
    for (int i = 0; i < n_cities; ++i) {
        int city = best_route->route[i];
        //printf("%d ", city);
        city_t tmp = (dataloader->cities)[city];
        fprintf(fp, "%d %d\n", tmp.x, tmp.y);
    }
    //printf("\n");

}