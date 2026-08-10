#ifndef FILTER_H
#define FILTER_H

#include <array>
#include <cstddef>
#include <algorithm>

class Filter{
    public:
        double update(double value) {
            for(size_t i=num_;i>0;i--){
                if(i < 5) buf_[i] = buf_[i-1];
            }
            buf_[0] = value;
            if(num_<5) num_++;
            std::array<double, 5> sorted = buf_;
            std::sort(sorted.begin(), sorted.begin() + num_);
            double median = sorted[num_ / 2];
            return median;
        }
    private:
        std::array<double, 5> buf_{};
        size_t num_ = 0;
};

#endif