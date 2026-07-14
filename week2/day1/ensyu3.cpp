#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>

class Sensor {
public:
    Sensor(uint32_t id, std::string name, float temperature) : id_(id), name_(name), temperature_(temperature){
        if(temperature_<-273.15) throw std::invalid_argument("とりえない温度の値です。");
    }

    uint32_t id() const {
        return id_;
    }
    std::string name() const {
        return name_;
    }
    float temperature() const {
        return temperature_;
    }

private:
    uint32_t id_;
    std::string name_;
    float temperature_;      // メンバは _ サフィックス(Google流。現場の規約に従う)
};

int main(void) {
    std::vector<Sensor> sensors = {
        Sensor(3, "temp_c", 10.0f),
        Sensor(1, "temp_a", 30.0f),
        Sensor(2, "temp_b", 20.0f)
    };

    //idSort
    std::sort(sensors.begin(), sensors.end(), [](const Sensor& a, const Sensor& b) {
        return a.id() < b.id();
    });
    for(size_t i=0;i<sensors.size();i++){
        std::cout << sensors[i].id() << ", " << sensors[i].name() << ", " << sensors[i].temperature() << ", " << std::endl;
    }

    //tempSort
    std::sort(sensors.begin(), sensors.end(), [](const Sensor& a, const Sensor& b) {
        return a.temperature() < b.temperature();
    });
    for(size_t i=0;i<sensors.size();i++){
        std::cout << sensors[i].id() << ", " << sensors[i].name() << ", " << sensors[i].temperature() << ", " << std::endl;
    }

    return 0;
}
