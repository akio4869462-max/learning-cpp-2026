#include <gtest/gtest.h>
#include <vector>
#include "Hysteresis.h"

TEST(Hysteresis, StaysOffBelowOnThreshold){
    Hysteresis h(2.0, -2.0);
    EXPECT_FALSE(h.update(1.0));
}

TEST(Hysteresis, TurnsOnWhenExceedingOnThreshold){
    Hysteresis h(2.0, -2.0);
    h.update(1.0);
    EXPECT_TRUE(h.update(3.0));
}

TEST(Hysteresis, TurnsOffWhenExceedingOffThreshold){
    Hysteresis h(2.0, -2.0);
    h.update(3.0);
    EXPECT_TRUE(h.update(3.0));
    EXPECT_FALSE(h.update(-3.0));
}

TEST(Hysteresis, StayOnInDeadZone){
    Hysteresis h(2.0, -2.0);
    h.update(3.0);
    EXPECT_TRUE(h.update(0.0));
}
