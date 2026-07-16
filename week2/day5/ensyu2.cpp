#include <functional>

class ITempSensor {
    public:
        virtual ~ITempSensor() = default;
        virtual float read() const = 0;
};

class FakeTempSensor : public ITempSensor {
    public:
        void set_value(float v){temp_ = v;};
        float read() const override {return temp_;};

    private:
        float temp_;
};

class TempMonitor {
    public:
        TempMonitor(ITempSensor& sensor, float threshold, std::function<void(float)> cb)
            : sensor_(sensor), threshold_(threshold), cb_(cb) {}

        void check() {
            float t = sensor_.read();
            if(t > threshold_) cb_(t);
        }

    private:
        ITempSensor& sensor_;              // 参照でセンサーを保持(所有はしない、借りているだけ)
        float threshold_;
        std::function<void(float)> cb_;
};

#include <iostream>

int main(){
    FakeTempSensor sensor;
    bool called = false;
    float received = 0.0f;

    TempMonitor monitor(sensor, 30.0f, [&](float t) {
        called = true;
        received = t;
    });

    sensor.set_value(29.0f);   // 閾値-1: 超えていないはず
    called = false;
    monitor.check();
    std::cout << "29.0 (閾値未満): " << (called ? "呼ばれた(NG)" : "呼ばれない(OK)") << std::endl;

    sensor.set_value(31.0f);   // 閾値+1: 超えているはず
    called = false;
    monitor.check();
    std::cout << "31.0 (閾値超え): " << (called ? "呼ばれた(OK)" : "呼ばれない(NG)") << std::endl;

    return 0;
}
