#include <vector>
#include <cstdint>
#include <iostream>

enum class Error { Ok, Timeout, BadArg, Busy, Empty };


template <typename T>
struct Result {
    T value{};
    Error error = Error::Ok;
    explicit operator bool() const { return error == Error::Ok; }
};

class Filter{
    public:
        explicit Filter(size_t capacity) : tempBuf_(capacity), pos_(0), count_(0) {}
        
        void push(float temp){
            tempBuf_[pos_] = temp;
            pos_ = (pos_ + 1) % tempBuf_.size();
            
            if (count_ != tempBuf_.size()) count_++;
        }

        Result<float> mean() const {
            if (count_ == 0) {
                return Result<float>{ 0.0f, Error::Empty };
            }
            float sum = 0.0f;
            for (size_t i = 0; i < count_; i++) {
                sum += tempBuf_[i];
            }
            return Result<float>{ sum / static_cast<float>(count_), Error::Ok };
        }

    private:
        std::vector<float> tempBuf_;
        size_t pos_, count_;
};

int main(){
    Filter f(3);

    if (auto r = f.mean()) {
        std::cout << "平均: " << r.value << std::endl;
    } else {
        std::cout << "まだデータがありません(想定通り)" << std::endl;
    }

    f.push(10.0f);
    f.push(20.0f);
    f.push(30.0f);

    if (auto r = f.mean()) {
        std::cout << "平均: " << r.value << std::endl;
    } else {
        std::cout << "データがありません" << std::endl;
    }

    return 0;
}
