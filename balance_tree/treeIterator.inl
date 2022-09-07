template <class Key, class Value>
TreeIterator<Key, Value>::TreeIterator() : m_cur(nullptr) {}

template <class Key, class Value>
TreeIterator<Key, Value>::TreeIterator(const TreeIterator &other) {
  *this = other;
}

template <class Key, class Value>
TreeIterator<Key, Value>::TreeIterator(NodeTree<Key, Value> *node)
    : m_cur(node) {}

template <class Key, class Value>
TreeIterator<Key, Value>::TreeIterator(TreeIterator &&other) {
  *this = std::move(other);
}

template <class Key, class Value>
TreeIterator<Key, Value>::~TreeIterator() {}

template <class Key, class Value>
TreeIterator<Key, Value> &TreeIterator<Key, Value>::operator=(
    const TreeIterator &other) {
  m_cur = other.m_cur;
  return *this;
}

template <class Key, class Value>
TreeIterator<Key, Value> &TreeIterator<Key, Value>::operator=(
    TreeIterator &&other) {
  m_cur = nullptr;
  std::swap(m_cur, other.m_cur);
  return *this;
}

template <class Key, class Value>
TreeIterator<Key, Value> &TreeIterator<Key, Value>::operator++() {
  TreeIncrement_();
  return *this;
}

template <class Key, class Value>
TreeIterator<Key, Value> TreeIterator<Key, Value>::operator++(int) {
  TreeIterator tmp = *this;
  TreeIncrement_();
  return tmp;
}

template <class Key, class Value>
TreeIterator<Key, Value> &TreeIterator<Key, Value>::operator--() {
  TreeDecrement_();
  return *this;
}

template <class Key, class Value>
TreeIterator<Key, Value> TreeIterator<Key, Value>::operator--(int) {
  TreeIterator tmp = *this;
  TreeDecrement_();
  return tmp;
}

template <class Key, class Value>
std::pair<const Key, Value> &TreeIterator<Key, Value>::operator*() {
  if (m_cur == nullptr) {
    throw std::out_of_range("iterator nullptr");
  }
  return m_cur->m_key_value;
}

template <class Key, class Value>
bool TreeIterator<Key, Value>::operator!=(const TreeIterator &other) {
  return (m_cur != other.m_cur);
}

template <class Key, class Value>
bool TreeIterator<Key, Value>::operator==(const TreeIterator &other) {
  return (m_cur == other.m_cur);
}

template <class Key, class Value>
void TreeIterator<Key, Value>::TreeIncrement_() {
  if (m_cur == nullptr) {
    throw std::out_of_range("iterator nullptr");
  }
  //  если у текущего узла есть правый потомок
  if (m_cur->m_node_right != nullptr) {
    m_cur = m_cur->m_node_right;
    while (m_cur->m_node_left != nullptr) {
      m_cur = m_cur->m_node_left;
    }
    //  если текущий узел является левым потомком родителя
  } else if (m_cur == m_cur->m_node_parent->m_node_left) {
    m_cur = m_cur->m_node_parent;
  } else {
    //  если текущий узел является правым потомком родителя
    NodeTree<Key, Value> *start_pos = m_cur;
    //  поднимаемся пока не станем левым потомком или не упремся в голову
    while (m_cur->m_node_parent != nullptr &&
           m_cur->m_key_value.first <= start_pos->m_key_value.first) {
      m_cur = m_cur->m_node_parent;
    }
    // если уперлись в голову дерева то возвращаемся в начало дерева
    if (m_cur->m_node_parent == nullptr &&
        m_cur->m_key_value.first <= start_pos->m_key_value.first) {
      m_cur = start_pos;
    }
  }
}

template <class Key, class Value>
void TreeIterator<Key, Value>::TreeDecrement_() {
  if (m_cur == nullptr) {
    throw std::out_of_range("iterator nullptr");
  }
  //  если у текущего узла есть левый потомок
  if (m_cur->m_node_left != nullptr) {
    m_cur = m_cur->m_node_left;
    while (m_cur->m_node_right != nullptr) {
      m_cur = m_cur->m_node_right;
    }
    //  если текущий узел является правым потомком родителя
  } else if (m_cur == m_cur->m_node_parent->m_node_right) {
    m_cur = m_cur->m_node_parent;
  } else {
    //  если текущий узел является левым потомком родителя
    NodeTree<Key, Value> *start_pos = m_cur;
    //  поднимаемся пока не станем правым потомком или не упремся в голову
    while (m_cur->m_node_parent != nullptr &&
           m_cur->m_key_value.first >= start_pos->m_key_value.first) {
      m_cur = m_cur->m_node_parent;
    }
    // если уперлись в голову дерева то уходим фэйковую ноду
    if (m_cur->m_node_parent == nullptr &&
        m_cur->m_key_value.first >= start_pos->m_key_value.first) {
      while (m_cur->m_node_right != nullptr) {
        m_cur = m_cur->m_node_right;
      }
    }
  }
}
