//
// Created by ZitengShu on 12/7/2021.
//

#ifndef PARALLEL_ANT_COLONY_SYSTEM_TIMER_H
#define PARALLEL_ANT_COLONY_SYSTEM_TIMER_H
#include <chrono>

typedef std::chrono::high_resolution_clock myclock;
typedef std::chrono::duration<double> dsec;
typedef std::chrono::time_point<std::chrono::high_resolution_clock> timer;
class Timer {
public:
    Timer();
    virtual ~Timer();
    void start();
    void end();
    double get_duration_time();

    timer start_time;
    timer end_time;
};


#endif //PARALLEL_ANT_COLONY_SYSTEM_TIMER_H
