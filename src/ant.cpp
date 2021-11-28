//
// Created by ZitengShu on 11/21/2021.
//

#include "ant.h"
Ant::Ant(int number_of_cities) {
    path = new Path(number_of_cities);
    tabu_list = new Tabu(number_of_cities);
    probe = new double[number_of_cities];
    for (int i = 0; i < number_of_cities; ++i) {
        probe[i] = 0.0;
    }
}

Ant::~Ant() {
    //printf("[DEBUG]: Start Ant\n");
    delete path;
    //printf("1\n");
    delete tabu_list;
    //printf("2\n");
    delete [] probe;
    //printf("[DEBUG]: End Ant\n");
}

void Ant::visit_city(int index, int city) {
    path->route[index] = city;
    tabu_list->list[city] = 1;
}

double Ant::get_length(Dataloader *dataloader) {
    return path->get_length(dataloader);
}

void Ant::print_tabu() {
    for (int i = 0; i < 131; ++i) {
        printf("%d ", tabu_list->list[i]);
    }
    printf("\n");
}

//TODO:segment fault
void Ant::update_probe(int start, int n_cities, Dataloader *dataloader,
                       double **phero, double alpha, double beta) {
    double sum = 0.0;
    for (int i = 0; i < n_cities; ++i) {
        if (tabu_list->is_visited(i)) {
            probe[i] = 0;
            printf("probe %d = 0\n", i);
       } else {
            printf("calc(%d, %d) ", start, i);
            double dis = (dataloader->distances)[start][i];
            printf("dis= %f ", dis);
            double ph = phero[start][i];
            printf("ph= %f ", ph);

            double dis_inv = 1.0 / dis;
            double ETA = pow(dis_inv, beta);
            printf("ETA= %f ", ETA);

            double TAU = pow(ph, alpha);
            printf("TAU= %f ", TAU);
            double prob_si = ETA * TAU;
            probe[i] = prob_si;
            printf("prob[%d]= %f", i, prob_si);
            sum += prob_si;
            printf("\n");
       }
    }
    printf("sum = %f\n", sum);
    for (int i = 0; i < n_cities; ++i) {
        probe[i] /= sum;
    }
}

void Ant::update_pheromone(double **phero, double Q, Dataloader *dataloader) {
    double length = path->get_length(dataloader);
    int max_itr = path->n_cities - 1;
    for (int i = 0; i < max_itr; ++i) {
        int start = path->route[i];
        int end = path->route[i+1];
        phero[start][end] +=  Q / length;
        phero[end][start] = phero[start][end];
    }
}

void Ant::reset() {
    path->reset();
    tabu_list->reset();
}