#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

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

#endif
