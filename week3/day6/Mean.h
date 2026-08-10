#ifndef MEAN_H
#define MEAN_H

#include <array>
#include <cstddef>
#include <algorithm>

class Mean{
    public:
        double update(double value) {
            double result = 0.0;
            for(size_t i=num_;i>0;i--){
                if(i < 5) buf_[i] = buf_[i-1];
            }
            buf_[0] = value;
            for(const auto& b : buf_){
                result += b;
            }
            if(num_<5) num_++;
            result /= num_;
            return result;
        };
    private:
        std::array<double, 5> buf_{};
        size_t num_ = 0;
};

#endif