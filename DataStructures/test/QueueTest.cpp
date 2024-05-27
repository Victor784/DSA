#include "Queue.hpp"
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

TEST(QueueTest,
     Queue_Default_constructor_creates_empty_stack_with_an_int_type) {
  Queue<int> myQueue;
  ASSERT_TRUE(myQueue.isEmpty());
}

TEST(QueueTest,
     Queue_Default_constructor_creates_empty_stack_with_an_user_defined_type) {
  Queue<custom_types::Point> myQueue;
  ASSERT_TRUE(myQueue.isEmpty());
}

TEST(QueueTest,
     Queue_isEmpty_returns_true_when_stack_is_empty_and_false_otherwise) {
  Queue<int> myQueue;
  ASSERT_TRUE(myQueue.isEmpty());
  myQueue.enqueue(1);
  EXPECT_FALSE(myQueue.isEmpty());
}

TEST(QueueTest,
     Queue_enque_adds_1_element_in_the_queue_at_the_back_of_the_queue) {
  Queue<int> myQueue;
  ASSERT_TRUE(myQueue.isEmpty());
  myQueue.enqueue(1);
  EXPECT_FALSE(myQueue.isEmpty());
  EXPECT_EQ(myQueue.front(), 1);
  myQueue.enqueue(2);
  EXPECT_FALSE(myQueue.isEmpty());
  EXPECT_EQ(myQueue.front(), 1);
  myQueue.enqueue(3);
  EXPECT_FALSE(myQueue.isEmpty());
  EXPECT_EQ(myQueue.front(), 1);
}

TEST(QueueTest, Queue_dequeue_removes_1_element_from_the_front_of_the_queue) {
  Queue<int> myQueue;
  ASSERT_TRUE(myQueue.isEmpty());
  myQueue.enqueue(1);
  EXPECT_FALSE(myQueue.isEmpty());
  myQueue.enqueue(2);
  myQueue.enqueue(3);
  myQueue.enqueue(4);

  EXPECT_EQ(myQueue.front(), 1);
  myQueue.dequeue();
  EXPECT_EQ(myQueue.front(), 2);
  myQueue.dequeue();
  EXPECT_EQ(myQueue.front(), 3);
  myQueue.dequeue();
  EXPECT_EQ(myQueue.front(), 4);
  myQueue.dequeue();
  ASSERT_TRUE(myQueue.isEmpty());
}

TEST(QueueTest,
     Queue_front_returns_the_value_of_the_first_element_without_removing_it) {
  Queue<int> myQueue;
  ASSERT_TRUE(myQueue.isEmpty());
  myQueue.enqueue(1);
  EXPECT_FALSE(myQueue.isEmpty());
  myQueue.enqueue(2);
  myQueue.enqueue(3);
  myQueue.enqueue(4);
  EXPECT_EQ(myQueue.front(), 1);
  EXPECT_EQ(myQueue.front(), 1);
  EXPECT_EQ(myQueue.front(), 1);
  EXPECT_EQ(myQueue.front(), 1);

  EXPECT_FALSE(myQueue.isEmpty());
  auto firstElement = myQueue.front();
  firstElement += 1;
  EXPECT_EQ(myQueue.front(), 1);
}

TEST(QueueTest, Queue_MoveConstructor_works_as_intended) {
  Queue<int> original;
  original.enqueue(10);
  original.enqueue(20);
  original.enqueue(30);
  Queue<int> moved(std::move(original));
  EXPECT_EQ(moved.front(), 10);
  moved.dequeue();
  EXPECT_EQ(moved.front(), 20);
  moved.dequeue();
  EXPECT_EQ(moved.front(), 30);
  moved.dequeue();
  EXPECT_TRUE(moved.isEmpty());
}

TEST(QueueTest, Queue_MoveAssignmentConstructor_works_as_intended) {
  Queue<int> original;
  original.enqueue(10);
  original.enqueue(20);
  original.enqueue(30);
  Queue<int> moved;
  moved = std::move(original);
  EXPECT_EQ(moved.front(), 10);
  moved.dequeue();
  EXPECT_EQ(moved.front(), 20);
  moved.dequeue();
  EXPECT_EQ(moved.front(), 30);
  moved.dequeue();
  EXPECT_TRUE(moved.isEmpty());
}

} // namespace test_construct
} // namespace tests

int main(int nArgs, char **vArgs) {
  ::testing::InitGoogleTest(&nArgs, vArgs);
  return RUN_ALL_TESTS();
}