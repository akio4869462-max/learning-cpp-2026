#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

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
    Sensor s(1, "temp0", 25.5f);
    std::cout << s.id() << " " << s.name() << " " << s.temperature() << "\n";

    try {
        Sensor bad(2, "broken", -300.0f);
    } catch (const std::invalid_argument& e) {
        std::cout << "例外: " << e.what() << "\n";
    }

    return 0;
}
