#ifndef HISTERESIS_H
#define HISTERESIS_H

#include <array>
#include <cstddef>
#include <algorithm>

class Hysteresis{
    public:
        Hysteresis(double on_threshold, double off_threshold)
        : on_threshold_(on_threshold), off_threshold_(off_threshold) {}

        bool update(double value){
            if(!on_ && value > on_threshold_) on_ = true;
            else if(on_ && value < off_threshold_) on_ = false;
            return on_;
        }
    private:
        bool on_ = false;
        double on_threshold_, off_threshold_;
};

#endif