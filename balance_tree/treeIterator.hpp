#pragma once

#include <iostream>

#include "nodeTree.hpp"

template <class Key, class Value>
class TreeIterator {
 public:
  TreeIterator();
  TreeIterator(const TreeIterator &other);
  explicit TreeIterator(NodeTree<Key, Value> *node);
  TreeIterator(TreeIterator &&other);
  ~TreeIterator();

  TreeIterator &operator=(const TreeIterator &other);
  TreeIterator &operator=(TreeIterator &&other);

  TreeIterator &operator++();
  TreeIterator operator++(int);

  TreeIterator &operator--();
  TreeIterator operator--(int);

  std::pair<const Key, Value> &operator*();

  bool operator!=(const TreeIterator &other);
  bool operator==(const TreeIterator &other);

 protected:
  void TreeIncrement_();
  void TreeDecrement_();

 protected:
  NodeTree<Key, Value> *m_cur;
};

#include "treeIterator.inl"
