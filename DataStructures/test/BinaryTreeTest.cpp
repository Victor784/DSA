#include "BinaryTree.hpp"
#include "BinarySearchTree.hpp"
#include "gtest/gtest.h"

using namespace vics_data_structures::binary_tree;

namespace tests {

TEST(BinarySearchTreeTest, InsertNodesAndVerifyStructure) {
  BinarySearchTree<int> bst;
  bst.insertNode(10);
  bst.insertNode(5);
  bst.insertNode(15);
  bst.insertNode(3);
  bst.insertNode(7);
  bst.insertNode(12);
  bst.insertNode(17);

  std::vector<int> inOrderResult;
  bst.traversal(BinaryTree<int>::TraversalType::InOrder,
                [&](const int &value) { inOrderResult.push_back(value); });

  std::vector<int> expected = {3, 5, 7, 10, 12, 15, 17};
  EXPECT_EQ(inOrderResult, expected);
}

TEST(BinarySearchTreeTest, DeleteNodeAndVerifyStructure) {
  BinarySearchTree<int> bst;
  bst.insertNode(10);
  bst.insertNode(5);
  bst.insertNode(15);
  bst.insertNode(3);
  bst.insertNode(7);
  bst.insertNode(12);
  bst.insertNode(17);

  bst.deleteTreeNode(15);

  std::vector<int> inOrderResult;
  bst.traversal(BinaryTree<int>::TraversalType::InOrder,
                [&](const int &value) { inOrderResult.push_back(value); });

  std::vector<int> expected = {3, 5, 7, 10, 12, 17};
  EXPECT_EQ(inOrderResult, expected);
}

TEST(BinarySearchTreeTest, GetHeight) {
  BinarySearchTree<int> bst;
  bst.insertNode(10);
  bst.insertNode(5);
  bst.insertNode(15);
  bst.insertNode(3);
  bst.insertNode(7);

  EXPECT_EQ(bst.getHeight(), 3);
}

TEST(BinarySearchTreeTest, GetNrOfNodes) {
  BinarySearchTree<int> bst;
  bst.insertNode(10);
  bst.insertNode(5);
  bst.insertNode(15);
  bst.insertNode(3);
  bst.insertNode(7);

  EXPECT_EQ(bst.getNrOfNodes(), 5);
}

TEST(BinarySearchTreeTest, TraversalTypes) {
  BinarySearchTree<int> bst;
  bst.insertNode(10);
  bst.insertNode(5);
  bst.insertNode(15);

  std::vector<int> preOrderResult;
  bst.traversal(BinaryTree<int>::TraversalType::PreOrder,
                [&](const int &value) { preOrderResult.push_back(value); });
  std::vector<int> preOrderExpected = {10, 5, 15};
  EXPECT_EQ(preOrderResult, preOrderExpected);

  std::vector<int> postOrderResult;
  bst.traversal(BinaryTree<int>::TraversalType::PostOrder,
                [&](const int &value) { postOrderResult.push_back(value); });
  std::vector<int> postOrderExpected = {5, 15, 10};
  EXPECT_EQ(postOrderResult, postOrderExpected);
}

} // namespace tests

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
