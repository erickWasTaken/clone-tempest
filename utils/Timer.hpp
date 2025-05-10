#ifndef TIMER_HPP
#define TIMER_HPP

#include "../utils/types.hpp"

class Timer{
private:
    u64 start;
    u64 stop;
    u32 maxMS;

public:
    Timer(u32 maxMS);
    ~Timer() = default;

    void Start();
    f64 Stop();
    f64 Delta();
};

#endif
