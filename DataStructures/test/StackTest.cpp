#include "Stack.hpp"
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

TEST(StackTest,
     Stack_Default_constructor_creates_empty_stack_with_an_int_type) {
  Stack<int> myStack;
  ASSERT_TRUE(myStack.isEmpty());
}

TEST(StackTest,
     Stack_Default_constructor_creates_empty_stack_with_an_user_defined_type) {
  Stack<custom_types::Point> myStack;
  ASSERT_TRUE(myStack.isEmpty());
}

TEST(StackTest,
     StackTest_isEmpty_returns_true_when_stack_is_empty_and_false_otherwise) {
  Stack<int> myStack;
  ASSERT_TRUE(myStack.isEmpty());
  myStack.push(1);
  EXPECT_FALSE(myStack.isEmpty());
}

TEST(StackTest, StackTest_push_adds_1_element_on_top_of_the_stack) {
  Stack<int> myStack;
  ASSERT_TRUE(myStack.isEmpty());
  myStack.push(1);
  EXPECT_FALSE(myStack.isEmpty());
  myStack.push(2);
  EXPECT_FALSE(myStack.isEmpty());
  myStack.push(3);
  EXPECT_FALSE(myStack.isEmpty());
}

TEST(
    StackTest,
    StackTest_pop_removes_1_element_from_the_top_of_the_stack_and_returns_popped_elem) {
  Stack<int> myStack;
  ASSERT_TRUE(myStack.isEmpty());
  myStack.push(1);
  EXPECT_FALSE(myStack.isEmpty());
  myStack.push(2);
  myStack.push(3);
  myStack.push(4);

  EXPECT_EQ(myStack.pop(), 4);
  EXPECT_EQ(myStack.pop(), 3);
  EXPECT_EQ(myStack.pop(), 2);
  EXPECT_EQ(myStack.pop(), 1);
  EXPECT_TRUE(myStack.isEmpty());
}

TEST(StackTest,
     StackTest_peek_returns_the_value_of_the_top_element_without_removing_it) {
  Stack<int> myStack;
  ASSERT_TRUE(myStack.isEmpty());
  myStack.push(1);
  EXPECT_FALSE(myStack.isEmpty());
  myStack.push(2);
  myStack.push(3);
  myStack.push(4);
  EXPECT_EQ(myStack.peek(), 4);
  EXPECT_EQ(myStack.peek(), 4);
  EXPECT_EQ(myStack.peek(), 4);
  EXPECT_EQ(myStack.peek(), 4);

  EXPECT_FALSE(myStack.isEmpty());
  const auto topElement = myStack.peek();
  EXPECT_EQ(myStack.peek(), 4);
}

TEST(StackTest, Stack_MoveConstructor_works_as_intended) {
  Stack<int> original;
  original.push(10);
  original.push(20);
  original.push(30);
  Stack<int> moved(std::move(original));
  EXPECT_EQ(moved.pop(), 30);
  EXPECT_EQ(moved.pop(), 20);
  EXPECT_EQ(moved.pop(), 10);
}

TEST(StackTest, StackTest_MoveAssignmentConstructor_works_as_intended) {
  Stack<int> original;
  original.push(10);
  original.push(20);
  original.push(30);
  Stack<int> moved;
  moved = std::move(original);
  EXPECT_EQ(moved.pop(), 30);
  EXPECT_EQ(moved.pop(), 20);
  EXPECT_EQ(moved.pop(), 10);
}

} // namespace test_construct
} // namespace tests

int main(int nArgs, char **vArgs) {
  ::testing::InitGoogleTest(&nArgs, vArgs);
  return RUN_ALL_TESTS();
}