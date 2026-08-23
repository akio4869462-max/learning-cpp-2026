#include "wave.h"

double attenuate(double amplitude, double depthCm){
    return amplitude * 0.5 * depthCm;
}