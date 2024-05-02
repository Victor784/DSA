#include "DoublyLinkedList.hpp"
#include "SinglyLinkedList.hpp"
#include "gtest/gtest.h"

using namespace vics_data_structures;
namespace tests {

namespace test_construct {

namespace custom_types {

// Define the Point class within the custom_types namespace
class Point {
public:
  Point(int x = 0, int y = 0) : m_x(x), m_y(y) {}
  int getX() const { return m_x; }
  int getY() const { return m_y; }

private:
  int m_x;
  int m_y;
};
} // namespace custom_types

TEST(LinkedListsTest, Test1) {
  //   vics_data_structures::arrays::DynamicArray<int> arr;
  //   ASSERT_EQ(arr.getCapacity(), 10); // Test that initial capacity is 10s
  //   EXPECT_EQ(arr.getLength(), 0);    // Init the size ptr is at the
  //   beggining size_t initialSize = 0; for (int i = 0; i < arr.getLength();
  //   ++i) {
  //     initialSize += sizeof(arr.get(i));
  //   }
  //   EXPECT_LE(initialSize,
  //             sizeof(size_t) * 2 +
  //                 sizeof(int) *
  //                     10); // Espect that the object is smaller than the sum
  //                     of
  //                          // all its contents as the m_data is saved on heap
  //   EXPECT_TRUE(arr.is_empty());
}

TEST(LinkedListsTest, Test2) {
  //   vics_data_structures::arrays::DynamicArray<char> arr;
  //   ASSERT_EQ(arr.getCapacity(), 10); // Test that initial capacity is 10s
  //   EXPECT_EQ(arr.getLength(), 0);    // Init the size ptr is at the
  //   beggining size_t initialSize = 0; for (int i = 0; i < arr.getLength();
  //   ++i) {
  //     initialSize += sizeof(arr.get(i));
  //   }
  //   EXPECT_LE(initialSize,
  //             sizeof(size_t) * 2 +
  //                 sizeof(char) *
  //                     10); // Espect that the object is smaller than the sum
  //                     of
  //                          // all its contents as the m_data is saved on heap
  //   EXPECT_TRUE(arr.is_empty());
}

TEST(LinkedListsTest, Test3) {
  // vics_data_structures::arrays::DynamicArray<custom_types::Point> arr;
  // ASSERT_EQ(arr.getCapacity(), 10); // Test that initial capacity is 10s
  //   EXPECT_EQ(arr.getLength(), 0);    // Init the size ptr is at the
  //   beggining size_t initialSize = 0; for (int i = 0; i < arr.getLength();
  //   ++i) {
  //     initialSize += sizeof(arr.get(i));
  //   }
  //   EXPECT_LE(initialSize,
  //             sizeof(size_t) * 2 +
  //                 sizeof(custom_types::Point) *
  //                     10); // Espect that the object is smaller than the sum
  //                     of
  //                          // all its contents as the m_data is saved on heap
  //   EXPECT_TRUE(arr.is_empty());
}

TEST(LinkedListsTest, Test4) {
  //   vics_data_structures::arrays::DynamicArray<int> arr;
  //   ASSERT_EQ(arr.getCapacity(), 10);
  //   EXPECT_EQ(arr.getLength(), 0);
  //   EXPECT_TRUE(arr.is_empty());

  //   arr.push_back(std::make_optional(1));
  //   EXPECT_EQ(arr.getLength(), 1);
  //   ASSERT_EQ(arr.getCapacity(), 10);
  //   EXPECT_EQ(arr.get(0), 1);

  //   arr.push_back(std::make_optional(2));
  //   EXPECT_EQ(arr.getLength(), 2);
  //   ASSERT_EQ(arr.getCapacity(), 10);
  //   EXPECT_EQ(arr.get(0), 1);
  //   EXPECT_EQ(arr.get(1), 2);

  //   arr.push_back(std::make_optional(3));
  //   arr.push_back(std::make_optional(4));
  //   arr.push_back(std::make_optional(5));
  //   arr.push_back(std::make_optional(6));
  //   arr.push_back(std::make_optional(7));
  //   arr.push_back(std::make_optional(8));
  //   arr.push_back(std::make_optional(9));
  //   EXPECT_EQ(arr.getLength(), 9);
  //   ASSERT_EQ(arr.getCapacity(), 10);
  //   arr.push_back(std::make_optional(10));
  //   arr.push_back(std::make_optional(11));
  //   EXPECT_EQ(arr.getLength(), 11);
  //   ASSERT_EQ(arr.getCapacity(), 20);
}

TEST(LinkedListsTest, Test5) {
  //   vics_data_structures::arrays::DynamicArray<int> arr;
  //   ASSERT_EQ(arr.getCapacity(), 10);
  //   EXPECT_EQ(arr.getLength(), 0);
  //   EXPECT_TRUE(arr.is_empty());

  //   EXPECT_EQ(arr.pop_back(), std::nullopt);
  //   EXPECT_EQ(arr.getLength(), 0);

  //   arr.push_back(std::make_optional(1));
  //   EXPECT_EQ(arr.getLength(), 1);
  //   arr.push_back(std::make_optional(2));
  //   EXPECT_EQ(arr.getLength(), 2);
  //   arr.push_back(std::make_optional(3));
  //   arr.push_back(std::make_optional(4));
  //   arr.push_back(std::make_optional(5));
  //   arr.push_back(std::make_optional(6));
  //   arr.push_back(std::make_optional(7));
  //   arr.push_back(std::make_optional(8));
  //   arr.push_back(std::make_optional(9));
  //   arr.push_back(std::make_optional(10));
  //   arr.push_back(std::make_optional(11));
  //   EXPECT_EQ(arr.getLength(), 11);
  //   ASSERT_EQ(arr.getCapacity(), 20);
  //   EXPECT_FALSE(arr.is_empty());

  //   const auto ret = arr.pop_back();
  //   ASSERT_EQ(arr.getLength(), 10);
  //   EXPECT_EQ(ret, 11);
  //   ASSERT_EQ(arr.getCapacity(), 20); // capacity does not change
}

TEST(LinkedListsTest, Test6) {
  // TODO uncomment test and run it after multithreadding safety implemented
  // vics_data_structures::arrays::DynamicArray<int> arr;
  // ASSERT_EQ(arr.getCapacity(), 10); // Test that initial capacity is 10s
  // EXPECT_EQ(arr.getLength(), 0);    // Init the size ptr is at the
  // EXPECT_TRUE(arr.is_empty());
  // arr.set(std::make_optional(1), index_t(10));
  // EXPECT_EQ(arr.getLength(), 10);
  // EXPECT_EQ(arr.getCapacity(), 20);
  // EXPECT_FALSE(arr.is_empty());
  // EXPECT_EQ(arr[0], std::nullopt);
  // EXPECT_EQ(arr[1], std::nullopt);
  // EXPECT_EQ(arr[2], std::nullopt);
  // EXPECT_EQ(arr[3], std::nullopt);
  // EXPECT_EQ(arr[4], std::nullopt);
  // EXPECT_EQ(arr[5], std::nullopt);
  // EXPECT_EQ(arr[6], std::nullopt);
  // EXPECT_EQ(arr[7], std::nullopt);
  // EXPECT_EQ(arr[8], std::nullopt);
  // EXPECT_EQ(arr[9], std::nullopt);
}

TEST(LinkedListsTest, Test7) {
  // vics_data_structures::arrays::DynamicArray<int> arr;
  // TODO uncomment test and run it after multithreadding safety implemented
  // ASSERT_EQ(arr.getCapacity(), 10); // Test that initial capacity is 10s
  // EXPECT_EQ(arr.getLength(), 0);    // Init the size ptr is at the
  // beggining
  // EXPECT_TRUE(arr.is_empty());
  // arr.set(std::make_optional(1), index_t(4));
  // EXPECT_EQ(arr.getLength(), 5);
  // EXPECT_EQ(arr.getCapacity(), 10);
  // EXPECT_FALSE(arr.is_empty());
  // EXPECT_EQ(arr[0], std::nullopt);
  // EXPECT_EQ(arr[1], std::nullopt);
  // EXPECT_EQ(arr[2], std::nullopt);
  // EXPECT_EQ(arr[3], std::nullopt);
  // EXPECT_EQ(arr[4], 1);
  // EXPECT_THROW({ arr.get(5); }, std::out_of_range);
  // EXPECT_EQ(arr.get(0), std::nullopt);
  // EXPECT_EQ(arr.get(4), 1);
}

} // namespace test_construct
} // namespace tests

int main(int nArgs, char **vArgs) {
  ::testing::InitGoogleTest(&nArgs, vArgs);
  return RUN_ALL_TESTS();
}