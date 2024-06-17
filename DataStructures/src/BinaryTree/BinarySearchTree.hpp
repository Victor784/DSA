#pragma once

#include "BinaryTree.hpp"

namespace vics_data_structures {

namespace binary_tree {

template <typename T> class BinarySearchTree : public BinaryTree<T> {
public:
  void insertNode(const T &value) override {
    std::unique_lock<std::shared_mutex> lock(this->tree_mutex);
    insertNode(this->root, value);
  }

  void deleteTreeNode(const T &value) override {
    std::unique_lock<std::shared_mutex> lock(this->tree_mutex);
    deleteNode(this->root, value);
  }

private:
  void insertNode(TreeNode<T> *&node, const T &value) {
    if (node == nullptr) {
      node = new TreeNode<T>(value);
    } else {
      if (value < node->data) {
        insertNode(node->left, value);
      } else {
        insertNode(node->right, value);
      }
    }
  }

  void deleteNode(TreeNode<T> *&node, const T &value) {
    if (node == nullptr) {
      return;
    }

    if (value < node->data) {
      deleteNode(node->left, value);
    } else if (value > node->data) {
      deleteNode(node->right, value);
    } else {
      // Case 1: No child or one child
      if (node->left == nullptr) {
        TreeNode<T> *temp = node->right;
        delete node;
        node = temp;
      } else if (node->right == nullptr) {
        TreeNode<T> *temp = node->left;
        delete node;
        node = temp;
      }
      // Case 2: Two children
      else {
        TreeNode<T> *temp = findMin(node->right);
        node->data = temp->data;
        deleteNode(node->right, temp->data);
      }
    }
  }

  TreeNode<T> *findMin(TreeNode<T> *node) {
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }
};
} // namespace binary_tree

} // namespace vics_data_structures