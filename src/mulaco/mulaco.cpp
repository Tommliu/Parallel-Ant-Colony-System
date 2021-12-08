//
// Created by ZitengShu on 12/8/2021.
//

#include "mulaco.h"
MulACO::MulACO(int number_of_ants, double initial_alpha, double initial_beta, double initial_q, double initial_rho, Dataloader *p_dataloader) : Model(number_of_ants, initial_alpha, initial_beta, initial_q, initial_rho, p_dataloader) {}
MulACO::~MulACO(){}