#include <gtest/gtest.h>
#include "math++/math.h"

TEST(Rotation, should_radians_to_degrees_f) {
    ASSERT_FLOAT_EQ(convert(RotationType::radians, RotationType::degrees, M_PI_2), 90);
}

TEST(Rotation, should_radians_to_degrees_d) {
    ASSERT_DOUBLE_EQ(convert(RotationType::radians, RotationType::degrees, M_PI_2), 90);
}

TEST(Rotation, should_degrees_to_radians_f) {
    ASSERT_FLOAT_EQ(convert(RotationType::degrees, RotationType::radians,90), M_PI_2);
}

TEST(Rotation, should_degrees_to_radians_d) {
    ASSERT_DOUBLE_EQ(convert(RotationType::degrees, RotationType::radians,90), M_PI_2);
}