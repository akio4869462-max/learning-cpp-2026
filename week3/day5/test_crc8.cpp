#include <gtest/gtest.h>
#include "crc8.h"

TEST(crc8, ZeroByteGiveZero) {
    uint8_t test[] = {0x00};
    uint8_t result =  crc8(test, 1);
    EXPECT_EQ(result, 0);
}

TEST(crc8, KnownTestVectorMatchesStandardValue) {
    uint8_t test2[] = {'1','2','3','4','5','6','7','8','9'};
    uint8_t result2 =  crc8(test2, 9);
    EXPECT_EQ(result2, 244);
}
