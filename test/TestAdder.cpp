//
// Created by Wolfgang on 26.03.18.
//

#include "gtest.h"
#include "Adder.h"

TEST(ADDER_TEST, TwoAndTwo) {
  ASSERT_EQ(add(2, 2), 4);
}
