//
// Created by ZitengShu on 12/7/2021.
//

#include "paco.h"
PACO::PACO(int number_of_ants, double initial_alpha, double initial_beta, double initial_q, double initial_rho, int max_iteration, Dataloader *p_dataloader): Model(number_of_ants, initial_alpha, initial_beta, initial_q, initial_rho, max_iteration, p_dataloader) {}

PACO::~PACO(){}