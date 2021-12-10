//
// Created by ZitengShu on 12/7/2021.
//

#include "timer.h"
Timer::Timer() {
    cumulative_time = 0.0;
}
Timer::~Timer() {}

void Timer::start() {
    start_time = myclock::now();
}

void Timer::end() {
    end_time = myclock::now();
}

void Timer::cum_start() {
    start_time = myclock::now();
}

void Timer::cum_end() {
    end_time = myclock::now();
    cumulative_time += std::chrono::duration_cast<dsec>(end_time - start_time).count();
}

double Timer::get_duration_time() {
    return std::chrono::duration_cast<dsec>(end_time - start_time).count();
}

double Timer::get_cumulative_time() {
    return cumulative_time;
}