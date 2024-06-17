/*This data structure is the basis for other more complex ones. As we need to
still take into account the concurent behaviour of this data structure the
structure of the class is changed. The nature of trees as a data structure is
that they can really easily use recursion, so the data protection tehnique would
have to change from lock_guards to something more lower level, like a
recursive_mutex that we lock/unlock by hand. Instead of doing this we are
modifying the way the class looks like so it has a public function that deals
with the locking and unlocking of the mutex (still using the RAII
method so the whole library uses the same tehnique) and on a deeper level the
buissnes logic is implemented in protected / private mehtods.*/

#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <mutex>
#include <shared_mutex>

namespace vics_data_structures {

namespace binary_tree {

template <typename T> struct TreeNode {
  T data;
  TreeNode *left;
  TreeNode *right;

  TreeNode(const T &value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T> class BinaryTree {

public:
  enum class TraversalType { InOrder, PreOrder, PostOrder };

protected:
  TreeNode<T> *root;
  mutable std::shared_mutex tree_mutex;

protected:
  void deleteTree(TreeNode<T> *node) {
    if (node != nullptr) {
      deleteTree(node->left);
      deleteTree(node->right);
      delete node;
    }
  }

public:
  BinaryTree() : root(nullptr) {}

  virtual ~BinaryTree() {
    std::unique_lock<std::shared_mutex> lock(tree_mutex);
    deleteTree(root);
  }

  virtual void insertNode(const T &value) = 0;

  virtual void deleteTreeNode(const T &value) = 0;

  void traversal(TraversalType traversalType,
                 const std::function<void(const T &)> &callback) const {
    std::shared_lock<std::shared_mutex> lock(tree_mutex);
    traversal(root, traversalType, callback);
  }

  int getHeight() const {
    std::shared_lock<std::shared_mutex> lock(tree_mutex);
    return getHeight(root);
  }

  int getNrOfNodes() const {
    std::shared_lock<std::shared_mutex> lock(tree_mutex);
    return getNrOfNodes(root);
  }

  bool isComplete() const {
    std::shared_lock<std::shared_mutex> lock(tree_mutex);
    return isComplete(root, 0, getNrOfNodes());
  }

protected:
  void traversal(TreeNode<T> *node, TraversalType traversalType,
                 const std::function<void(const T &)> &callback) const {
    if (node == nullptr)
      return;
    switch (traversalType) {
    case TraversalType::InOrder:
      traversal(node->left, traversalType, callback);
      callback(node->data);
      traversal(node->right, traversalType, callback);
      break;
    case TraversalType::PreOrder:
      callback(node->data);
      traversal(node->left, traversalType, callback);
      traversal(node->right, traversalType, callback);
      break;
    case TraversalType::PostOrder:
      traversal(node->left, traversalType, callback);
      traversal(node->right, traversalType, callback);
      callback(node->data);
      break;
    }
  }

  int getHeight(TreeNode<T> *node) const {
    if (node == nullptr)
      return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return std::max(leftHeight, rightHeight) + 1;
  }

  int getNrOfNodes(TreeNode<T> *node) const {
    if (node == nullptr)
      return 0;
    return getNrOfNodes(node->left) + getNrOfNodes(node->right) + 1;
  }

  bool isComplete(TreeNode<T> *node, int index, int numNodes) const {
    if (node == nullptr)
      return true;

    if (index >= numNodes)
      return false;

    return (isComplete(node->left, 2 * index + 1, numNodes) &&
            isComplete(node->right, 2 * index + 2, numNodes));
  }
};

template <typename T> class BinarySearchTree : public BinaryTree<T> {

public:
  void insertNode(const T &value) override {
    std::unique_lock<std::shared_mutex> lock(this->tree_mutex);
    insertNode(this->root, value);
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
};

template <typename T> class CompleteBinaryTree : public BinaryTree<T> {

public:
  void insertNode(const T &value) override {
    std::unique_lock<std::shared_mutex> lock(this->tree_mutex);
    insertNode(this->root, value);
  }

private:
  void insertNode(TreeNode<T> *&node, const T &value, int index = 0) {
    if (node == nullptr) {
      node = new TreeNode<T>(value);
    } else {
      if (index < this->getNrOfNodes()) {
        if (index < (this->getNrOfNodes() / 2)) {
          insertNode(node->left, value, 2 * index + 1);
        } else {
          insertNode(node->right, value, 2 * index + 2);
        }
      }
    }
  }
};

} // namespace binary_tree

} // namespace vics_data_structures
