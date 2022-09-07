#pragma once

#include <iostream>

template <class Key, class Value>
struct NodeTree {
 public:
  NodeTree(const std::pair<Key, Value> &key_value, NodeTree *node_parent,
           NodeTree *node_right, NodeTree *node_left)
      : m_key_value(key_value),
        m_node_parent(node_parent),
        m_node_right(node_right),
        m_node_left(node_left),
        m_bf(0),
        m_right_deep(0),
        m_left_deep(0) {}

  std::pair<const Key, Value> m_key_value;
  NodeTree *m_node_parent;
  NodeTree *m_node_right;
  NodeTree *m_node_left;
  int m_bf;          //  balence factor
  int m_right_deep;  //  right branch deep
  int m_left_deep;   //  left branch deep
};
