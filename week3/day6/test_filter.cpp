#include <gtest/gtest.h>
#include <vector>
#include "Filter.h"

TEST(Filter, MedianOfSingleValueIsItself){
    Filter f;
    EXPECT_EQ(f.update(10.0), 10.0);
}

TEST(Filter, MedianOfThreeValues){
    Filter f;
    f.update(10.0);
    f.update(30.0);
    double result = f.update(20.0);
    EXPECT_EQ(result, 20.0);
}

TEST(Filter, SpikeDoesNotDragMedian){
    Filter f;
    f.update(10.0);
    f.update(11.0);
    f.update(9.0);
    double result = f.update(1000.0);
    EXPECT_EQ(result, 11.0);
}

TEST(Filter, CheckMaxCapacity){
    Filter f;
    f.update(9.0);
    f.update(10.0);
    f.update(11.0);
    f.update(12.0);
    double result1 = f.update(13.0);
    EXPECT_EQ(result1, 11.0);
    double result2 = f.update(14.0);
    EXPECT_EQ(result2, 12.0);
}
