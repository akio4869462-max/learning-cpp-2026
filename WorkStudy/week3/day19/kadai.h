#ifndef KADAI_H
#define KADAI_H

#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>

class EchoLine{
    public:
        EchoLine(int num) : sample_(num){}
        size_t size() const { return sample_.size(); }
        void set(size_t i, double v){ sample_.at(i) = v;}
        double get(size_t i) const { return sample_.at(i); }
        double maxAmplitude() const {
            if(sample_.empty()) return 0.0;
            auto it = std::max_element(sample_.begin(), sample_.end(), [](double a, double b) { return std::abs(a) < std::abs(b); });
            return std::abs(*it);
        }
        void applyGain(double gain){
            std::transform(sample_.begin(), sample_.end(), sample_.begin(), [gain](double s){ return s * gain; });
        }
        EchoLine normalized() const {
            EchoLine copy = *this;
            if(maxAmplitude() == 0.0){
                throw std::invalid_argument("sample all zero"); //全要素0なら例外
            }
            copy.applyGain(1.0 / maxAmplitude());
            return copy;
        }
    private:
        std::vector<double> sample_;
};

#endif