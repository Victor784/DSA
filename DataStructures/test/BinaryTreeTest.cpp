#include "BinarySearchTree.hpp"
#include "CompleteBinaryTree.hpp"
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

TEST(BinaryTreeTest, BinaryTree_constructor_works_as_expected) {
  //   vics_data_structures::arrays::DynamicArray<int> arr;
  //   ASSERT_EQ(arr.getCapacity(), 10); // Test that initial capacity is 10s
  //   EXPECT_EQ(arr.getLength(), 0);    // Init the size ptr is at the
  //   beggining size_t initialSize = 0; for (int i = 0; i < arr.getLength();
  //   ++i) {
  //     initialSize += sizeof(arr[i]);
  //   }
  //   EXPECT_LE(initialSize,
  //             sizeof(size_t) * 2 +
  //                 sizeof(int) *
  //                     10); // Espect that the object is smaller than the sum
  //                     of
  //                          // all its contents as the m_data is saved on heap
  //   EXPECT_TRUE(arr.is_empty());
}

TEST(BinaryTreeTest, BinarySearchTree_insertNode_add_one_element) {
  //   vics_data_structures::arrays::DynamicArray<char> arr;
  //   ASSERT_EQ(arr.getCapacity(), 10); // Test that initial capacity is 10s
  //   EXPECT_EQ(arr.getLength(), 0);    // Init the size ptr is at the
  //   beggining size_t initialSize = 0; for (int i = 0; i < arr.getLength();
  //   ++i) {
  //     initialSize += sizeof(arr[i]);
  //   }
  //   EXPECT_LE(initialSize,
  //             sizeof(size_t) * 2 +
  //                 sizeof(char) *
  //                     10); // Espect that the object is smaller than the sum
  //                     of
  //                          // all its contents as the m_data is saved on heap
  //   EXPECT_TRUE(arr.is_empty());
}

TEST(BinaryTreeTest, BinarySearchTree_deleteTreeNode_erases_one_element) {
  //   vics_data_structures::arrays::DynamicArray<char> arr;
  //   ASSERT_EQ(arr.getCapacity(), 10); // Test that initial capacity is 10s
  //   EXPECT_EQ(arr.getLength(), 0);    // Init the size ptr is at the
  //   beggining size_t initialSize = 0; for (int i = 0; i < arr.getLength();
  //   ++i) {
  //     initialSize += sizeof(arr[i]);
  //   }
  //   EXPECT_LE(initialSize,
  //             sizeof(size_t) * 2 +
  //                 sizeof(char) *
  //                     10); // Espect that the object is smaller than the sum
  //                     of
  //                          // all its contents as the m_data is saved on heap
  //   EXPECT_TRUE(arr.is_empty());
}

TEST(BinaryTreeTest, CompleteBinaryTree_deleteTreeNode_erases_one_element) {
  //   vics_data_structures::arrays::DynamicArray<custom_types::Point> arr;
  //   ASSERT_EQ(arr.getCapacity(), 10); // Test that initial capacity is 10s
  //   EXPECT_EQ(arr.getLength(), 0);    // Init the size ptr is at the
  //   beggining size_t initialSize = 0; for (int i = 0; i < arr.getLength();
  //   ++i) {
  //     initialSize += sizeof(arr[i]);
  //   }
  //   EXPECT_LE(initialSize,
  //             sizeof(size_t) * 2 +
  //                 sizeof(custom_types::Point) *
  //                     10); // Espect that the object is smaller than the sum
  //                     of
  //                          // all its contents as the m_data is saved on heap
  //   EXPECT_TRUE(arr.is_empty());
}

TEST(BinaryTreeTest, BinaryTree_traversal_works) {
  //   vics_data_structures::arrays::DynamicArray<int> arr;
  //   ASSERT_EQ(arr.getCapacity(), 10);
  //   EXPECT_EQ(arr.getLength(), 0);
  //   EXPECT_TRUE(arr.is_empty());

  //   arr.push_back(1);
  //   EXPECT_EQ(arr.getLength(), 1);
  //   ASSERT_EQ(arr.getCapacity(), 10);
  //   EXPECT_EQ(arr[0], 1);

  //   arr.push_back(2);
  //   EXPECT_EQ(arr.getLength(), 2);
  //   ASSERT_EQ(arr.getCapacity(), 10);
  //   EXPECT_EQ(arr[0], 1);
  //   EXPECT_EQ(arr[1], 2);

  //   arr.push_back(3);
  //   arr.push_back(4);
  //   arr.push_back(5);
  //   arr.push_back(6);
  //   arr.push_back(7);
  //   arr.push_back(8);
  //   arr.push_back(9);
  //   EXPECT_EQ(arr.getLength(), 9);
  //   ASSERT_EQ(arr.getCapacity(), 10);
  //   arr.push_back(10);
  //   arr.push_back(11);
  //   EXPECT_EQ(arr.getLength(), 11);
  //   ASSERT_EQ(arr.getCapacity(), 20);
}

TEST(BinaryTreeTest, BinaryTree_getHeight_works) {
  //   vics_data_structures::arrays::DynamicArray<int> arr;
  //   ASSERT_EQ(arr.getCapacity(), 10);
  //   EXPECT_EQ(arr.getLength(), 0);
  //   EXPECT_TRUE(arr.is_empty());

  //   EXPECT_EQ(arr.pop_back(), nullptr);
  //   EXPECT_EQ(arr.getLength(), 0);

  //   arr.push_back(1);
  //   EXPECT_EQ(arr.getLength(), 1);
  //   arr.push_back(2);
  //   EXPECT_EQ(arr.getLength(), 2);
  //   arr.push_back(3);
  //   arr.push_back(4);
  //   arr.push_back(5);
  //   arr.push_back(6);
  //   arr.push_back(7);
  //   arr.push_back(8);
  //   arr.push_back(9);
  //   arr.push_back(10);
  //   arr.push_back(11);
  //   EXPECT_EQ(arr.getLength(), 11);
  //   ASSERT_EQ(arr.getCapacity(), 20);
  //   EXPECT_FALSE(arr.is_empty());

  //   const auto ret = *arr.pop_back();
  //   ASSERT_EQ(arr.getLength(), 10);
  //   EXPECT_EQ(ret, 11);
  //   ASSERT_EQ(arr.getCapacity(), 20); // capacity does not change
}

TEST(BinaryTreeTest, BinaryTree_getNrOfNodes_works) {
  //   vics_data_structures::arrays::DynamicArray<int> arr;
  //   ASSERT_EQ(arr.getCapacity(), 10);
  //   EXPECT_EQ(arr.getLength(), 0);
  //   EXPECT_TRUE(arr.is_empty());

  //   EXPECT_EQ(arr.pop_back(), nullptr);
  //   EXPECT_EQ(arr.getLength(), 0);

  //   arr.push_back(1);
  //   EXPECT_EQ(arr.getLength(), 1);
  //   arr.push_back(2);
  //   EXPECT_EQ(arr.getLength(), 2);
  //   arr.push_back(3);
  //   arr.push_back(4);
  //   arr.push_back(5);
  //   arr.push_back(6);
  //   arr.push_back(7);
  //   arr.push_back(8);
  //   arr.push_back(9);
  //   arr.push_back(10);
  //   arr.push_back(11);
  //   EXPECT_EQ(arr.getLength(), 11);
  //   ASSERT_EQ(arr.getCapacity(), 20);
  //   EXPECT_FALSE(arr.is_empty());

  //   const auto ret = *arr.pop_back();
  //   ASSERT_EQ(arr.getLength(), 10);
  //   EXPECT_EQ(ret, 11);
  //   ASSERT_EQ(arr.getCapacity(), 20); // capacity does not change
}

TEST(BinaryTreeTest, BinaryTree_isComplete_works) {
  //   vics_data_structures::arrays::DynamicArray<int> arr;
  //   ASSERT_EQ(arr.getCapacity(), 10);
  //   EXPECT_EQ(arr.getLength(), 0);
  //   EXPECT_TRUE(arr.is_empty());

  //   EXPECT_EQ(arr.pop_back(), nullptr);
  //   EXPECT_EQ(arr.getLength(), 0);

  //   arr.push_back(1);
  //   EXPECT_EQ(arr.getLength(), 1);
  //   arr.push_back(2);
  //   EXPECT_EQ(arr.getLength(), 2);
  //   arr.push_back(3);
  //   arr.push_back(4);
  //   arr.push_back(5);
  //   arr.push_back(6);
  //   arr.push_back(7);
  //   arr.push_back(8);
  //   arr.push_back(9);
  //   arr.push_back(10);
  //   arr.push_back(11);
  //   EXPECT_EQ(arr.getLength(), 11);
  //   ASSERT_EQ(arr.getCapacity(), 20);
  //   EXPECT_FALSE(arr.is_empty());

  //   const auto ret = *arr.pop_back();
  //   ASSERT_EQ(arr.getLength(), 10);
  //   EXPECT_EQ(ret, 11);
  //   ASSERT_EQ(arr.getCapacity(), 20); // capacity does not change
}

} // namespace test_construct
} // namespace tests

int main(int nArgs, char **vArgs) {
  ::testing::InitGoogleTest(&nArgs, vArgs);
  return RUN_ALL_TESTS();
}