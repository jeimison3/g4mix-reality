#ifndef __SDLKIT_FREQUENT
#define __SDLKIT_FREQUENT
#include <chrono>

class Frequent{
    private:
        unsigned iCounter;
        unsigned Period;
        float realPeriod;
        float IPS;
        std::chrono::time_point<std::chrono::system_clock> lastCall, secCall;
    public:
        Frequent(int Hz);
        bool isReady();
        unsigned getIPS();
        float getPeriod();
};

#endif