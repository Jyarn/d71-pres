#include <iostream>
#include <chrono>
#include <omp.h>

#include "trace.h"

void
trc_init(struct trc_time_struct* t)
{
        auto tm = std::chrono::high_resolution_clock::now();
    auto dur = tm.time_since_epoch();

    t->start =
        std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
}

void
trc_tock(struct trc_time_struct* t)
{
        auto tm = std::chrono::high_resolution_clock::now();
    auto dur = tm.time_since_epoch();

    auto new_start =
        std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

    std::cerr << omp_get_max_threads() << "," << new_start - t->start << "\n";
}
