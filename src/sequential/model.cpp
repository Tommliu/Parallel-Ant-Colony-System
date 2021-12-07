//
// Created by ZitengShu on 11/21/2021.
//

#include "model.h"
#define UNUSED __attribute__((unused))
Model::Model() {}

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

    ants = new Ant[n_ants];
    pheromone = new double* [n_cities];

    for (int i = 0; i < n_cities; i++) {
        pheromone[i] = new double [n_cities];

        for (int j = 0; j < n_cities; j++) {
            pheromone[i][j] = 1.0;
        }
    }
    for (int i = 0; i < n_ants; ++i) {
        ants[i].initialize(n_cities);
    }
}

Model::~Model() {
    for (int i = 0; i < n_cities; i++) {
        delete [] pheromone[i];
    }
    delete [] pheromone;

    for (int i = 0; i < n_ants; ++i) {
        ants[i].release();
    }
    delete [] ants;
}

void Model::random_place_ants() {
    for (int i = 0; i < n_ants; ++i) {
        int city = random.get_initial_city(n_cities);
        ants[i].reset();
        ants[i].visit_city(0, city);
        ants[i].visit_city(n_cities, city);
    }
}

void Model::construct_routes() {
    for (int i = 0; i < n_ants; ++i) {
        for (int j = 1; j < n_cities; ++j) {
            int next_city = random.get_next_city(&(ants[i]), (ants[i].path.route)[j-1],
                                                  n_cities, dataloader, pheromone, alpha, beta);
            ants[i].visit_city(j, next_city);
        }
        double length = ants[i].get_length(dataloader);
        if (length < local_best.length) {
            local_best = Solution(length, i, ants[i].path);
        }
    }
    if (local_best.length < global_best.length) {
        global_best = local_best;
    }
    local_best.rest();// = static_cast<double>(INT_MAX);
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
    ants[local_best.iant].update_pheromone(pheromone, q, dataloader);
}

void Model::solve(int max_iter) {
    for (int i = 0; i < max_iter; ++i) {
        random_place_ants();
        // update best route
        construct_routes();
        update_pheromone();
    }
}

void Model::write_output(const char* UNUSED input_path, int n_cores, double duration_time) {
    int result = access("./output", F_OK);
    if (result) {
        int res = mkdir("./output", 0755);
        if (res) {
            printf("[ERROR]: Create directory %d\n", errno);
        }
    }

    std::string test_path = std::string(input_path);
    size_t pos1 = test_path.find("tests");
    size_t pos2 = test_path.find(".tsp");
    size_t test_name_length = pos2 - pos1 - 6;
    std::string test_name = test_path.substr(pos1+6, test_name_length);

    std::string test_dir_name = "./output/" + test_name + "/";
    std::string output_path = test_dir_name + test_name + "_" + std::to_string(n_cores);
    std::string profile_path = test_dir_name + test_name + "_profile";
    result = access(test_dir_name.c_str(), F_OK);
    if (result) {
        int res = mkdir(test_dir_name.c_str(), 0755);
        if (res) {
            printf("[ERROR]: Create directory %d\n", errno);
        }
    }

    FILE *fp_profile = fopen(profile_path.c_str(), "a+");
    if (fp_profile == nullptr) {
        printf("[ERROR]:failed to open output file\n");
    }
    fprintf(fp_profile, "COMPUTATION TIME (%d) : %lf\n", n_cores, duration_time);
    fprintf(fp_profile, "TOUR_LENGTH (%d) : %lf\n", n_cores, global_best.length);

    fclose(fp_profile);

    FILE *fp = fopen(output_path.c_str(), "w");
    if (fp == nullptr) {
        printf("[ERROR]:failed to open output file\n");
    }

    fprintf(fp, "NAME: %s\n", test_name.c_str());
    fprintf(fp, "DISTANCE: %lf\n", global_best.length);
    fprintf(fp, "DIMENSION: %d\n", n_cities);

    int max_itr = n_cities + 1;
    for (int i = 0; i < max_itr; ++i) {
        int city = global_best.path.route[i];
        city_t tmp = (dataloader->cities)[city];
        fprintf(fp, "%d %d\n", tmp.x, tmp.y);
    }
    fclose(fp);
}