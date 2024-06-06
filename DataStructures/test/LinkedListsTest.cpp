#include "DoublyLinkedList.hpp"
#include "SinglyLinkedList.hpp"
#include "gtest/gtest.h"
#include <algorithm>

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

using namespace vics_data_structures::linked_lists;

TEST(LinkedListsTest,
     SinglyLinkedList_Default_constructor_constructs_emepty_list) {
  singly_linked_list::SinglyLinkedList<int> list;

  // Verify that the list is empty after construction
  ASSERT_TRUE(list.is_empty());
  ASSERT_EQ(list.getSize(), 0);
}

TEST(LinkedListsTest,
     SinglyLinkedList_Move_constructor_constructs_another_list_correctly) {
  singly_linked_list::SinglyLinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  singly_linked_list::SinglyLinkedList<int> list2(std::move(list1));

  // Verify that list2 has taken ownership of the elements from list1
  ASSERT_TRUE(list1.is_empty());
  ASSERT_EQ(list2.front(), 1);
  ASSERT_EQ(list2.getSize(), 2);
}

TEST(
    LinkedListsTest,
    SinglyLinkedList_Move_assignment_constructor_constructs_another_list_correctly) {
  // Create a source SinglyLinkedList
  singly_linked_list::SinglyLinkedList<int> sourceList;
  sourceList.push_back(1);
  sourceList.push_back(2);
  sourceList.push_back(3);

  // Create a destination SinglyLinkedList
  singly_linked_list::SinglyLinkedList<int> destinationList;
  destinationList.push_back(4);
  destinationList.push_back(5);

  // Perform move assignment
  destinationList = std::move(sourceList);

  // Check if the destination list has been properly moved
  ASSERT_EQ(destinationList.getSize(), 3); // Check if size is 3
  ASSERT_EQ(destinationList.front(), 1);   // Check if first element is 1
  ASSERT_EQ(destinationList.back(), 3);    // Check if last element is 3

  // Check if the source list is now empty
  ASSERT_EQ(sourceList.getSize(), 0);
}

TEST(
    LinkedListsTest,
    SinglyLinkedList_Default_constructor_with_custom_type_works_just_as_intended) {
  singly_linked_list::SinglyLinkedList<custom_types::Point> list;
  ASSERT_TRUE(list.is_empty());
  ASSERT_EQ(list.getSize(), 0);
  custom_types::Point point1{1, 2};
  custom_types::Point point2{3, 4};
  custom_types::Point point3{5, 6};
  list.push_back(point1);
  list.push_back(point2);
  list.push_back(point3);
  ASSERT_EQ(list.getSize(), 3);
  ASSERT_EQ(list.getHeadNode()->data.getX(), 1);
  ASSERT_EQ(list.getHeadNode()->data.getY(), 2);
  ASSERT_EQ(list.getTailNode()->data.getX(), 5);
  ASSERT_EQ(list.getTailNode()->data.getY(), 6);
}

TEST(
    LinkedListsTest,
    SinglyLinkedList_get_head_node_returns_first_element_in_list_and_get_tail_node_retunrs_last) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 3);
}

TEST(
    LinkedListsTest,
    SinglyLinkedList_clear_removes_all_elements_and_sets_extreme_nodes_to_null) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  list.clear();
  EXPECT_EQ(list.getSize(), 0);
  ASSERT_EQ(list.getHeadNode(), nullptr);
  ASSERT_EQ(list.getTailNode(), nullptr);
}

TEST(LinkedListsTest, SinglyLinkedList_begin_returns_interator_for_head_node) {
  singly_linked_list::SinglyLinkedList<int> list;
  // EXPECT_EQ(list.begin()->data, 1);
  EXPECT_EQ(list.begin(), list.getHeadNode());
}
TEST(LinkedListsTest, SinglyLinkedList_end_returns_interator_over_tail_node) {
  singly_linked_list::SinglyLinkedList<int> list;
  EXPECT_EQ(list.end(), list.getTailNode());
}
TEST(LinkedListsTest,
     SinglyLinkedList_push_front_inserts_new_node_with_empty_list) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_front(1);
  ASSERT_EQ(list.getSize(), 1);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 1);
}
TEST(
    LinkedListsTest,
    SinglyLinkedList_push_front_inserts_new_node_before_head_with_non_empty_list) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  list.push_front(3);
  EXPECT_EQ(list.getSize(), 3);
  EXPECT_EQ(list.getHeadNode()->data, 3);
}
TEST(LinkedListsTest,
     SinglyLinkedList_push_back_inserts_new_node_with_empty_list) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_back(1);
  ASSERT_EQ(list.getSize(), 1);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 1);
}
TEST(
    LinkedListsTest,
    SinglyLinkedList_push_back_inserts_new_node_after_tail_with_non_empty_list) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_front(1);
  list.push_front(2);
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.getTailNode()->data, 1);
  list.push_back(3);
  EXPECT_EQ(list.getSize(), 3);
  EXPECT_EQ(list.getTailNode()->data, 3);
}
TEST(LinkedListsTest, SinglyLinkedList_insert_inserts_new_node_on_valid_index) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 2);
  list.insert(3, 1);
  ASSERT_EQ(list.getSize(), 3);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 2);
}

TEST(LinkedListsTest,
     SinglyLinkedList_insert_inserts_new_node_before_head_on_index_eq_0) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 2);
  list.insert(3, 0);
  ASSERT_EQ(list.getSize(), 3);
  EXPECT_EQ(list.getHeadNode()->data, 3);
  EXPECT_EQ(list.getTailNode()->data, 2);
}
TEST(
    LinkedListsTest,
    SinglyLinkedList_insert_inserts_new_node_after_tail_on_index_higher_than_size) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 2);
  list.insert(3, 3);
  ASSERT_EQ(list.getSize(), 3);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 3);

  list.insert(4, 4);
  ASSERT_EQ(list.getSize(), 4);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 4);

  list.insert(5, 7);
  ASSERT_EQ(list.getSize(), 5);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 5);
}
TEST(LinkedListsTest,
     SinglyLinkedList_pop_front_returns_null_opt_for_empty_list) {
  singly_linked_list::SinglyLinkedList<int> list;
  ASSERT_EQ(list.getSize(), 0);
  EXPECT_THROW(list.pop_front(), std::out_of_range);
}
TEST(LinkedListsTest,
     SinglyLinkedList_pop_front_deletes_head_node_and_returns_its_value) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  const auto ret = list.pop_front();
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(ret, 1);
  EXPECT_EQ(list.getHeadNode()->data, 2);
}
TEST(LinkedListsTest,
     SinglyLinkedList_pop_back_returns_null_opt_for_empty_list) {
  singly_linked_list::SinglyLinkedList<int> list;
  ASSERT_EQ(list.getSize(), 0);
  EXPECT_THROW(list.pop_back(), std::out_of_range);
}
TEST(LinkedListsTest,
     SinglyLinkedList_pop_back_deletes_tail_node_and_returns_its_value) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  const auto ret = list.pop_back();
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(ret, 3);
  EXPECT_EQ(list.getTailNode()->data, 2);
}
TEST(LinkedListsTest, SinglyLinkedList_erase_deletes_head_node_for_index_eq_0) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  list.erase(0);
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.getHeadNode()->data, 2);
}
TEST(LinkedListsTest,
     SinglyLinkedList_erase_deletes_tail_node_for_index_eq_size) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  list.erase(2);
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.getTailNode()->data, 2);
}
TEST(LinkedListsTest, SinglyLinkedList_erase_throws_for_empty_list) {
  singly_linked_list::SinglyLinkedList<int> list;
  ASSERT_EQ(list.getSize(), 0);
  EXPECT_THROW(list.erase(0), std::out_of_range);
}

TEST(LinkedListsTest, SinglyLinkedList_erase_deletes_node_at_index) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  list.erase(1);
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 3);
}
TEST(LinkedListsTest, SinglyLinkedList_front_returns_data_from_head_node) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  const auto front = list.front();
  EXPECT_EQ(front, 1);
}
TEST(LinkedListsTest, SinglyLinkedList_back_returns_data_from_tail_node) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  const auto back = list.back();
  EXPECT_EQ(back, 3);
}
TEST(LinkedListsTest,
     SinglyLinkedList_square_brackets_operator_trows_for_index_out_of_range) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  EXPECT_THROW(list[4], std::out_of_range);
}
TEST(LinkedListsTest,
     SinglyLinkedList_square_brackets_operator_returns_data_at_index) {
  singly_linked_list::SinglyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  EXPECT_EQ(list[0], 1);
  EXPECT_EQ(list[1], 2);
  EXPECT_EQ(list[2], 3);
}
TEST(
    LinkedListsTest,
    SinglyLinkedList_is_empty_returns_true_if_list_is_empty_and_false_otherwise) {
  singly_linked_list::SinglyLinkedList<int> list;
  EXPECT_TRUE(list.is_empty());
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  EXPECT_FALSE(list.is_empty());
}

TEST(LinkedListsTest, SinglyLinkedList_iterator_can_be_used_to_navigate_list) {
  singly_linked_list::SinglyLinkedList<int> list;
  EXPECT_TRUE(list.is_empty());
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  ASSERT_EQ(list.getSize(), 3);
  ASSERT_EQ(list[0], 1);
  ASSERT_EQ(list[1], 2);
  ASSERT_EQ(list[2], 3);
  auto it = list.begin();
  ASSERT_EQ(it->data, 1);
  it++;
  ASSERT_EQ(it->data, 2);
  it++;
  ASSERT_EQ(it->data, 3);
}

TEST(LinkedListsTest, SinglyLinkedList_can_be_used_in_std_find_alg) {
  singly_linked_list::SinglyLinkedList<int> list;
  EXPECT_TRUE(list.is_empty());
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  auto result = std::find(list.begin(), list.end(), *list.getHeadNode());
  ASSERT_NE(result, list.end());
  ASSERT_EQ(result->data, 1);
  result = std::find(list.begin(), list.end(), *(list.getTailNode() + 1));
  ASSERT_EQ(result, list.end());
}

// DoublyLinkedListTests

TEST(LinkedListsTest,
     DoublyLinkedList_Default_constructor_constructs_emepty_list) {
  doubly_linked_list::DoublyLinkedList<int> list;

  // Verify that the list is empty after construction
  ASSERT_TRUE(list.is_empty());
  ASSERT_EQ(list.getSize(), 0);
}

TEST(LinkedListsTest,
     DoublyLinkedList_Move_constructor_constructs_another_list_correctly) {
  doubly_linked_list::DoublyLinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  doubly_linked_list::DoublyLinkedList<int> list2(std::move(list1));

  // Verify that list2 has taken ownership of the elements from list1
  ASSERT_TRUE(list1.is_empty());
  ASSERT_EQ(list2.front(), 1);
  ASSERT_EQ(list2.getSize(), 2);
}

TEST(
    LinkedListsTest,
    DoublyLinkedList_Move_assignment_constructor_constructs_another_list_correctly) {

  doubly_linked_list::DoublyLinkedList<int> sourceList;
  sourceList.push_back(1);
  sourceList.push_back(2);
  sourceList.push_back(3);

  doubly_linked_list::DoublyLinkedList<int> destinationList;
  destinationList.push_back(4);
  destinationList.push_back(5);

  // Perform move assignment
  destinationList = std::move(sourceList);

  // Check if the destination list has been properly moved
  ASSERT_EQ(destinationList.getSize(), 3); // Check if size is 3
  ASSERT_EQ(destinationList.front(), 1);   // Check if first element is 1
  ASSERT_EQ(destinationList.back(), 3);    // Check if last element is 3

  // Check if the source list is now empty
  ASSERT_EQ(sourceList.getSize(), 0);
}

TEST(
    LinkedListsTest,
    DoublyLinkedList_Default_constructor_with_custom_type_works_just_as_intended) {
  doubly_linked_list::DoublyLinkedList<custom_types::Point> list;
  ASSERT_TRUE(list.is_empty());
  ASSERT_EQ(list.getSize(), 0);
  custom_types::Point point1{1, 2};
  custom_types::Point point2{3, 4};
  custom_types::Point point3{5, 6};
  list.push_back(point1);
  list.push_back(point2);
  list.push_back(point3);
  ASSERT_EQ(list.getSize(), 3);
  ASSERT_EQ(list.getHeadNode()->data.getX(), 1);
  ASSERT_EQ(list.getHeadNode()->data.getY(), 2);
  ASSERT_EQ(list.getTailNode()->data.getX(), 5);
  ASSERT_EQ(list.getTailNode()->data.getY(), 6);
}

TEST(
    LinkedListsTest,
    DoublyLinkedList_get_head_node_returns_first_element_in_list_and_get_tail_node_retunrs_last) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 3);
}

TEST(
    LinkedListsTest,
    DoublyLinkedList_clear_removes_all_elements_and_sets_extreme_nodes_to_null) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  list.clear();
  EXPECT_EQ(list.getSize(), 0);
  ASSERT_EQ(list.getHeadNode(), nullptr);
  ASSERT_EQ(list.getTailNode(), nullptr);
}

TEST(LinkedListsTest, DoublyLinkedList_begin_returns_interator_for_head_node) {
  doubly_linked_list::DoublyLinkedList<int> list;
  // EXPECT_EQ(list.begin()->data, 1);
  EXPECT_EQ(list.begin(), list.getHeadNode());
}
TEST(LinkedListsTest, DoublyLinkedList_end_returns_interator_over_tail_node) {
  doubly_linked_list::DoublyLinkedList<int> list;
  EXPECT_EQ(list.end(), list.getTailNode());
}
TEST(LinkedListsTest,
     DoublyLinkedList_push_front_inserts_new_node_with_empty_list) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_front(1);
  ASSERT_EQ(list.getSize(), 1);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 1);
}
TEST(
    LinkedListsTest,
    DoublyLinkedList_push_front_inserts_new_node_before_head_with_non_empty_list) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  list.push_front(3);
  EXPECT_EQ(list.getSize(), 3);
  EXPECT_EQ(list.getHeadNode()->data, 3);
}
TEST(LinkedListsTest,
     DoublyLinkedList_push_back_inserts_new_node_with_empty_list) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_back(1);
  ASSERT_EQ(list.getSize(), 1);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 1);
}
TEST(
    LinkedListsTest,
    DoublyLinkedList_push_back_inserts_new_node_after_tail_with_non_empty_list) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_front(1);
  list.push_front(2);
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.getTailNode()->data, 1);
  list.push_back(3);
  EXPECT_EQ(list.getSize(), 3);
  EXPECT_EQ(list.getTailNode()->data, 3);
}
TEST(LinkedListsTest, DoublyLinkedList_insert_inserts_new_node_on_valid_index) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 2);
  list.insert(3, 1);
  ASSERT_EQ(list.getSize(), 3);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 2);
}

TEST(LinkedListsTest,
     DoublyLinkedList_insert_inserts_new_node_before_head_on_index_eq_0) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 2);
  list.insert(3, 0);
  ASSERT_EQ(list.getSize(), 3);
  EXPECT_EQ(list.getHeadNode()->data, 3);
  EXPECT_EQ(list.getTailNode()->data, 2);
}
TEST(
    LinkedListsTest,
    DoublyLinkedList_insert_inserts_new_node_after_tail_on_index_higher_than_size) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 2);
  list.insert(3, 3);
  ASSERT_EQ(list.getSize(), 3);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 3);

  list.insert(4, 4);
  ASSERT_EQ(list.getSize(), 4);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 4);

  list.insert(5, 7);
  ASSERT_EQ(list.getSize(), 5);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 5);
}
TEST(LinkedListsTest,
     DoublyLinkedList_pop_front_returns_null_opt_for_empty_list) {
  doubly_linked_list::DoublyLinkedList<int> list;
  ASSERT_EQ(list.getSize(), 0);
  EXPECT_THROW(list.pop_front();, std::out_of_range);
}
TEST(LinkedListsTest,
     DoublyLinkedList_pop_front_deletes_head_node_and_returns_its_value) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  const auto ret = list.pop_front();
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(ret, 1);
  EXPECT_EQ(list.getHeadNode()->data, 2);
}
TEST(LinkedListsTest,
     DoublyLinkedList_pop_back_returns_null_opt_for_empty_list) {
  doubly_linked_list::DoublyLinkedList<int> list;
  ASSERT_EQ(list.getSize(), 0);
  EXPECT_THROW(list.pop_front();, std::out_of_range);
}
TEST(LinkedListsTest,
     DoublyLinkedList_pop_back_deletes_tail_node_and_returns_its_value) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  const auto ret = list.pop_back();
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(ret, 3);
  EXPECT_EQ(list.getTailNode()->data, 2);
}
TEST(LinkedListsTest, DoublyLinkedList_erase_deletes_head_node_for_index_eq_0) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  list.erase(0);
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.getHeadNode()->data, 2);
}
TEST(LinkedListsTest,
     DoublyLinkedList_erase_deletes_tail_node_for_index_eq_size) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  list.erase(2);
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.getTailNode()->data, 2);
}
TEST(LinkedListsTest, DoublyLinkedList_erase_throws_for_empty_list) {
  doubly_linked_list::DoublyLinkedList<int> list;
  ASSERT_EQ(list.getSize(), 0);
  EXPECT_THROW(list.erase(0), std::out_of_range);
}

TEST(LinkedListsTest, DoublyLinkedList_erase_deletes_node_at_index) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  list.erase(1);
  ASSERT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.getHeadNode()->data, 1);
  EXPECT_EQ(list.getTailNode()->data, 3);
}
TEST(LinkedListsTest, DoublyLinkedList_front_returns_data_from_head_node) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  const auto front = list.front();
  EXPECT_EQ(front, 1);
}
TEST(LinkedListsTest, DoublyLinkedList_back_returns_data_from_tail_node) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  const auto back = list.back();
  EXPECT_EQ(back, 3);
}
TEST(LinkedListsTest,
     DoublyLinkedList_square_brackets_operator_trows_for_index_out_of_range) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  EXPECT_THROW(list[4], std::out_of_range);
}
TEST(LinkedListsTest,
     DoublyLinkedList_square_brackets_operator_returns_data_at_index) {
  doubly_linked_list::DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(list.getSize(), 3);
  EXPECT_EQ(list[0], 1);
  EXPECT_EQ(list[1], 2);
  EXPECT_EQ(list[2], 3);
}
TEST(
    LinkedListsTest,
    DoublyLinkedList_is_empty_returns_true_if_list_is_empty_and_false_otherwise) {
  doubly_linked_list::DoublyLinkedList<int> list;
  EXPECT_TRUE(list.is_empty());
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  EXPECT_FALSE(list.is_empty());
}

TEST(LinkedListsTest,
     DoublyLinkedList_iterator_can_be_used_to_navigate_list_from_begin_to_end) {
  doubly_linked_list::DoublyLinkedList<int> list;
  EXPECT_TRUE(list.is_empty());
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  ASSERT_EQ(list.getSize(), 3);
  ASSERT_EQ(list[0], 1);
  ASSERT_EQ(list[1], 2);
  ASSERT_EQ(list[2], 3);
  auto it = list.begin();
  ASSERT_EQ(it->data, 1);
  it++;
  ASSERT_EQ(it->data, 2);
  it++;
  ASSERT_EQ(it->data, 3);
}

TEST(LinkedListsTest,
     DoublyLinkedList_iterator_can_be_used_to_navigate_list_from_end_to_begin) {
  doubly_linked_list::DoublyLinkedList<int> list;
  EXPECT_TRUE(list.is_empty());
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  ASSERT_EQ(list.getSize(), 3);
  ASSERT_EQ(list[0], 1);
  ASSERT_EQ(list[1], 2);
  ASSERT_EQ(list[2], 3);
  auto it = list.end();
  ASSERT_EQ(it->data, 3);
  it--;
  ASSERT_EQ(it->data, 2);
  it--;
  ASSERT_EQ(it->data, 1);
}

TEST(LinkedListsTest, DoublyLinkedList_can_be_used_in_std_find_alg) {
  doubly_linked_list::DoublyLinkedList<int> list;
  EXPECT_TRUE(list.is_empty());
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  auto result = std::find(list.begin(), list.end(), *list.getHeadNode());
  ASSERT_NE(result, list.end());
  ASSERT_EQ(result->data, 1);
  result = std::find(list.begin(), list.end(), *(list.getTailNode() + 1));
  ASSERT_EQ(result, list.end());
}

} // namespace test_construct
} // namespace tests

int main(int nArgs, char **vArgs) {
  ::testing::InitGoogleTest(&nArgs, vArgs);
  return RUN_ALL_TESTS();
}