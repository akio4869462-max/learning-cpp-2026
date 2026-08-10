#ifndef PICONTROLLER_H
#define PICONTROLLER_H

#include <fstream>
#include <iostream>

class PIController {
    public:
        PIController(double kp, double ki) : kp_(kp), ki_(ki) {}
        double update(double error, double dt){
            error_sum_ += error * dt;
            return kp_ * error + ki_ * error_sum_;
        }
    private:
        double kp_, ki_;
        double error_sum_ = 0.0;
};

#endif