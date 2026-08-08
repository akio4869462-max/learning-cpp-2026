#ifndef OVEN_CONTROLLER_H
#define OVEN_CONTROLLER_H

// ハードウェア操作を抽象化したインターフェース
class ITempSensor {
public:
    virtual ~ITempSensor() = default;
    virtual double read() const = 0;
};

// テスト用の偽物: 好きな値を自由に設定できる
class FakeTempSensor : public ITempSensor {
public:
    void setValue(double v) { value_ = v; }
    double read() const override { return value_; }
private:
    double value_ = 0.0;
};

// 制御ロジック: ITempSensor経由でしかセンサーに触れない
class OvenController {
public:
    explicit OvenController(ITempSensor& sensor) : sensor_(sensor) {}
    bool shouldHeat() const { return sensor_.read() < 50.0; }
private:
    ITempSensor& sensor_;
};

#endif
