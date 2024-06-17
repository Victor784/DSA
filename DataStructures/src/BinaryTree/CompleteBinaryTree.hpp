#pragma once

#include "BinaryTree.hpp"

namespace vics_data_structures {

namespace binary_tree {

template <typename T> class CompleteBinaryTree : public BinaryTree<T> {
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
  void insertNode(TreeNode<T> *&node, const T &value, int index = 0) {
    if (node == nullptr) {
      node = new TreeNode<T>(value);
    } else {
      if (index < this->getNrOfNodes(node)) {
        if (index < (this->getNrOfNodes(node) / 2)) {
          insertNode(node->left, value, 2 * index + 1);
        } else {
          insertNode(node->right, value, 2 * index + 2);
        }
      }
    }
  }

  void deleteNode(TreeNode<T> *&node, const T &value, int index = 0) {
    if (node == nullptr) {
      return;
    }

    if (index < this->getNrOfNodes(node)) {
      if (index == 0) {
        // Special case: root node deletion
        deleteTree(node);
        node = nullptr;
      } else {
        if (index < (this->getNrOfNodes(node) / 2)) {
          deleteNode(node->left, value, 2 * index + 1);
        } else {
          deleteNode(node->right, value, 2 * index + 2);
        }
      }
    }
  }
};
} // namespace binary_tree

} // namespace vics_data_structures