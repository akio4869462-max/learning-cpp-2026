#include <variant>
#include <iostream>



int main(){
    std::variant<int, float, std::string> sensor_value;
    
    auto printer = [](auto&& value) {
        using T = std::decay_t<decltype(value)>;
        if constexpr (std::is_same_v<T, int>) {
            std::cout << value << "はint型の数値です。" << std::endl;
        } else if constexpr (std::is_same_v<T, float>) {
            std::cout << value << "はfloat型の数値です。" << std::endl;
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << value << "は文字列です。" << std::endl;
        }
    };

    sensor_value = 42;
    std::visit(printer, sensor_value);

    sensor_value = 3.14f;
    std::visit(printer, sensor_value);

    sensor_value = std::string("error");
    std::visit(printer, sensor_value);

    return 0;
}