#include "Frequent.hpp"

Frequent::Frequent(int Hz){
    this->Period = 1000/Hz;
    this->lastCall = this->secCall = std::chrono::system_clock::now();
    this->realPeriod = 0;
    this->iCounter = 0;
    this->IPS = 0;
}

bool Frequent::isReady(){
    
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    unsigned long long millis = std::chrono::duration_cast<std::chrono::milliseconds>
        (now-this->lastCall).count();

    unsigned long diffMilis = std::chrono::duration_cast<std::chrono::milliseconds>
        (now-this->secCall).count();
    if( diffMilis >= 1000){
        this->secCall = now;
        this->IPS = iCounter;
        this->realPeriod = (diffMilis*1.0)/iCounter;
        this->iCounter = 0;
    }
    if( millis < this->Period ) return false;

    this->lastCall = now;
    iCounter++;
    return true;
}

unsigned Frequent::getIPS(){
    return this->IPS;
}

float Frequent::getPeriod(){
    return this->realPeriod;
}