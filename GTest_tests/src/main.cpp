#include <iostream>

#include "gtest/gtest.h"

TEST(EqualTests, Base)
{
  ASSERT_EQ(0, 0);
}

TEST(EqualTests, ExpectTest)
{
  EXPECT_NE(0, 0);
  EXPECT_EQ(0, 0);
  int i = 0;
  ++i;
  EXPECT_GT(1, i);
  EXPECT_GT(2, i);
}

TEST(EqualTests, AssertTest)
{
  ASSERT_NE(0, 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}