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
int main(){
    double T = 20.0;
    double target = 50.0;
    double gain = 1.0, tau = 5.0, dt = 0.1;
    double kp = 2.0, ki = 0.5;
    PIController pi = PIController(kp, ki);
    std::ofstream csv("output3.csv");

    for(int i = 0;i < 200; i++){
        double error = target - T;
        // double u = kp * error;
        double u = pi.update(error, dt);
        T += (u * gain - T) * dt / tau;
        csv << i << "," << T << std::endl;
    }
}