#include <gtest/gtest.h>
#include "deboucer.h"
#include <vector>

TEST(Deboucer, ForthContinuous) {
    std::vector<bool> test = {1,1,1,1};
    Deboucer db;
    bool result;
    for(size_t i = 0;i < test.size(); i++){
        result = db.update(test[i]);
    }
    EXPECT_EQ(result, 1);
}

TEST(Deboucer, NotForthContinuous) {
    std::vector<bool> test = {0,0,0,0};
    Deboucer db;
    bool result;
    for(size_t i = 0;i < test.size(); i++){
        result = db.update(test[i]);
    }
    EXPECT_EQ(result, 0);
}

TEST(Deboucer, ContinuousKeep) {
    std::vector<bool> test = {1,1,1,1,0,0,0};
    Deboucer db;
    bool result;
    for(size_t i = 0;i < test.size(); i++){
        result = db.update(test[i]);
    }
    EXPECT_EQ(result, 1);
}
