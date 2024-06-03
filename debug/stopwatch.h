#pragma once
#include <chrono>


class Stopwatch {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

public:
    Stopwatch() {
        start();
    }

    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    double elapsed_time() {
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end_time - start_time;
        return elapsed.count();
    }
};