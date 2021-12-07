//
// Created by ZitengShu on 12/7/2021.
//

#include "timer.h"
Timer::Timer() {}
Timer::~Timer() {}

void Timer::start() {
    start_time = myclock::now();
}

void Timer::end() {
    end_time = myclock::now();
}

double Timer::get_duration_time() {
    return std::chrono::duration_cast<dsec>(end_time - start_time).count();
}