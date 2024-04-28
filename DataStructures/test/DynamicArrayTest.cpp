#include "DynamicArray.hpp"
#include "gtest/gtest.h"

using namespace vics_data_structures;
namespace tests {
namespace test_construct {
TEST(DynamicArrayTest, BasicAssertions) {
  vics_data_structures::arrays::DynamicArray<int> arr;
  ASSERT_EQ(arr.getCapacity(), 10); // Test that initial capacity is 10s
  EXPECT_EQ(arr.getLength(),
            0); // Initially the size pointer is at the beggining of the array
}
} // namespace test_construct
} // namespace tests

int main(int nArgs, char **vArgs) {
  ::testing::InitGoogleTest(&nArgs, vArgs);
  return RUN_ALL_TESTS();
}