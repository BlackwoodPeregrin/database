#include <fstream>

template <class Key, class Value>
AvlBalanceTree<Key, Value>::AvlBalanceTree()
    : m_root(nullptr), m_begin(nullptr), m_end(nullptr), m_size(0) {}

template <class Key, class Value>
AvlBalanceTree<Key, Value>::AvlBalanceTree(const AvlBalanceTree &other)
    : m_root(nullptr), m_begin(nullptr), m_end(nullptr), m_size(0) {
  *this = other;
}

template <class Key, class Value>
AvlBalanceTree<Key, Value>::AvlBalanceTree(
    const std::initializer_list<std::pair<Key, Value>> &items)
    : m_root(nullptr), m_begin(nullptr), m_end(nullptr), m_size(0) {
  for (const auto &count : items) {
    Insert(count);
  }
}

template <class Key, class Value>
AvlBalanceTree<Key, Value>::AvlBalanceTree(AvlBalanceTree &&other)
    : m_root(nullptr), m_begin(nullptr), m_end(nullptr), m_size(0) {
  *this = std::move(other);
}

template <class Key, class Value>
AvlBalanceTree<Key, Value>::~AvlBalanceTree() {
  Clear();
}

template <class Key, class Value>
AvlBalanceTree<Key, Value> &AvlBalanceTree<Key, Value>::operator=(
    const AvlBalanceTree &other) {
  if (this != &other) {
    Clear();
    if (other.m_root != nullptr) {
      m_root = new NodeTree<Key, Value>(other.m_root->m_key_value, nullptr,
                                        nullptr, nullptr);
      // копируем все дерево
      CopyNode_(m_root, other.m_root);
      m_size = other.m_size;
      // устанавливаем begin
      NodeTree<Key, Value> *cur = m_root;
      while (cur->m_node_left != nullptr) {
        cur = cur->m_node_left;
      }
      m_begin = cur;
      // устанавливаем end
      cur = m_root;
      while (cur->m_node_right != nullptr) {
        cur = cur->m_node_right;
      }
      m_end = cur;
    }
  }
  return *this;
}

template <class Key, class Value>
AvlBalanceTree<Key, Value> &AvlBalanceTree<Key, Value>::operator=(
    AvlBalanceTree &&other) {
  if (this != &other) {
    Clear();
    std::swap(m_root, other.m_root);
    std::swap(m_begin, other.m_begin);
    std::swap(m_end, other.m_end);
    std::swap(m_size, other.m_size);
  }
  return *this;
}

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::Clear() {
  if (m_root != nullptr) {
    DeleteAllNodes_(m_root);
    m_begin = nullptr;
    m_end = nullptr;
    m_size = 0;
  }
}

template <class Key, class Value>
size_t AvlBalanceTree<Key, Value>::Size() {
  return m_size;
}

template <class Key, class Value>
bool AvlBalanceTree<Key, Value>::IsEmpty() {
  return (m_root == nullptr);
}

/* =================== Class Iterator ===================== */

template <class Key, class Value>
AvlBalanceTree<Key, Value>::Iterator::Iterator() : TreeIterator<Key, Value>() {}

template <class Key, class Value>
AvlBalanceTree<Key, Value>::Iterator::Iterator(const Iterator &other)
    : TreeIterator<Key, Value>(other) {}

template <class Key, class Value>
AvlBalanceTree<Key, Value>::Iterator::Iterator(NodeTree<Key, Value> *node)
    : TreeIterator<Key, Value>(node) {}

template <class Key, class Value>
AvlBalanceTree<Key, Value>::Iterator::Iterator(Iterator &&other)
    : TreeIterator<Key, Value>(std::move(other)) {}

template <class Key, class Value>
AvlBalanceTree<Key, Value>::Iterator::~Iterator() {}

template <class Key, class Value>
typename AvlBalanceTree<Key, Value>::Iterator &
AvlBalanceTree<Key, Value>::Iterator::operator=(const Iterator &other) {
  TreeIterator<Key, Value>::operator=(other);
  return *this;
}

template <class Key, class Value>
typename AvlBalanceTree<Key, Value>::Iterator &
AvlBalanceTree<Key, Value>::Iterator::operator=(Iterator &&other) {
  TreeIterator<Key, Value>::operator=(std::move(other));
  return *this;
}

template <class Key, class Value>
bool AvlBalanceTree<Key, Value>::Iterator::operator!=(const Iterator &other) {
  return TreeIterator<Key, Value>::operator!=(other);
}

template <class Key, class Value>
bool AvlBalanceTree<Key, Value>::Iterator::operator==(const Iterator &other) {
  return TreeIterator<Key, Value>::operator==(other);
}

/* ======================================================== */

template <class Key, class Value>
typename AvlBalanceTree<Key, Value>::Iterator
AvlBalanceTree<Key, Value>::begin() {
  return Iterator(m_begin);
}

template <class Key, class Value>
typename AvlBalanceTree<Key, Value>::Iterator
AvlBalanceTree<Key, Value>::end() {
  return Iterator(m_end);
}

/* ================= Class Const Iterator ================= */

template <class Key, class Value>
AvlBalanceTree<Key, Value>::ConstIterator::ConstIterator() : Iterator() {}

template <class Key, class Value>
AvlBalanceTree<Key, Value>::ConstIterator::ConstIterator(
    const ConstIterator &other)
    : Iterator(other) {}

template <class Key, class Value>
AvlBalanceTree<Key, Value>::ConstIterator::ConstIterator(
    NodeTree<Key, Value> *node)
    : Iterator(node) {}

template <class Key, class Value>
AvlBalanceTree<Key, Value>::ConstIterator::ConstIterator(ConstIterator &&other)
    : Iterator(std::move(other)) {}

template <class Key, class Value>
AvlBalanceTree<Key, Value>::ConstIterator::~ConstIterator() {}

template <class Key, class Value>
typename AvlBalanceTree<Key, Value>::ConstIterator &
AvlBalanceTree<Key, Value>::ConstIterator::operator=(
    const ConstIterator &other) {
  Iterator::operator=(other);
  return *this;
}

template <class Key, class Value>
typename AvlBalanceTree<Key, Value>::ConstIterator &
AvlBalanceTree<Key, Value>::ConstIterator::operator=(ConstIterator &&other) {
  Iterator::operator=(std::move(other));
  return *this;
}

template <class Key, class Value>
bool AvlBalanceTree<Key, Value>::ConstIterator::operator!=(
    const ConstIterator &other) {
  return Iterator::operator!=(other);
}

template <class Key, class Value>
bool AvlBalanceTree<Key, Value>::ConstIterator::operator==(
    const ConstIterator &other) {
  return Iterator::operator==(other);
}

template <class Key, class Value>
const std::pair<const Key, Value>
    &AvlBalanceTree<Key, Value>::ConstIterator::operator*() {
  return Iterator::operator*();
}

/* ======================================================== */

template <class Key, class Value>
typename AvlBalanceTree<Key, Value>::ConstIterator
AvlBalanceTree<Key, Value>::cbegin() {
  return ConstIterator(m_begin);
}

template <class Key, class Value>
typename AvlBalanceTree<Key, Value>::ConstIterator
AvlBalanceTree<Key, Value>::cend() {
  return ConstIterator(m_end);
}

template <class Key, class Value>
bool AvlBalanceTree<Key, Value>::Contains(const Key &key) {
  if (Find(key) != end()) {
    return true;
  }
  return false;
}

template <class Key, class Value>
typename AvlBalanceTree<Key, Value>::Iterator AvlBalanceTree<Key, Value>::Find(
    const Key &key) {
  NodeTree<Key, Value> *current = m_root;
  while (current != nullptr) {
    if (key > current->m_key_value.first) {
      current = current->m_node_right;
    } else if (key < current->m_key_value.first) {
      current = current->m_node_left;
    } else {
      return Iterator(current);
    }
  }
  return end();
}

template <class Key, class Value>
std::pair<typename AvlBalanceTree<Key, Value>::Iterator, bool>
AvlBalanceTree<Key, Value>::Insert(const std::pair<Key, Value> &key_value) {
  Iterator iter;
  size_t size = m_size;
  if (m_root == nullptr) {
    iter = AddFirstElement_(key_value);
  } else {
    iter = AddOtherElement_(key_value, m_root);
  }
  return std::make_pair(iter, size != m_size);
}

template <class Key, class Value>
std::pair<typename AvlBalanceTree<Key, Value>::Iterator, bool>
AvlBalanceTree<Key, Value>::Insert(const Key &key, const Value &value) {
  std::pair<Key, Value> key_value(key, value);
  return Insert(key_value);
}

template <class Key, class Value>
bool AvlBalanceTree<Key, Value>::Erase(Iterator pos) {
  if (pos != end()) {
    Key search_key = (*pos).first;
    return Erase(search_key);
  } else {
    return false;
  }
}

template <class Key, class Value>
bool AvlBalanceTree<Key, Value>::Erase(const Key &key) {
  NodeTree<Key, Value> *delete_node = m_root;
  while (delete_node != nullptr) {
    if (key > delete_node->m_key_value.first) {
      delete_node = delete_node->m_node_right;
    } else if (key < delete_node->m_key_value.first) {
      delete_node = delete_node->m_node_left;
    } else {
      break;
    }
  }
  // элемент с таким ключом не найден
  if (delete_node == nullptr) {
    return false;
  }

  // если удаляем максимальный элемент в дереве, удаляем и end
  if (m_end->m_node_parent == delete_node) {
    delete_node->m_node_right = nullptr;
    delete m_end;
    m_end = nullptr;
  }
  // если удаляем минимальный элемент в дереве, зануляем begin
  if (m_begin == delete_node) {
    m_begin = nullptr;
  }
  // если удаляемый элемент является корнем дерева
  if (delete_node->m_node_parent == nullptr) {
    EraceRoot_(delete_node);
  } else {
    // если у удаляемого эоемента нет потомков
    if (delete_node->m_node_right == nullptr &&
        delete_node->m_node_left == nullptr) {
      EraceWithoutKids_(delete_node);
      // если у удаляемого элемента один потомок
    } else if ((delete_node->m_node_right == nullptr &&
                delete_node->m_node_left != nullptr) ||
               (delete_node->m_node_right != nullptr &&
                delete_node->m_node_left == nullptr)) {
      EraceWithOneKid_(delete_node);
    } else {
      // если у удаляемого элемента два потомок
      EraceWithTwoKids_(delete_node);
    }
  }
  // обновляем begin
  if (m_begin == nullptr) {
    EraceChangeBegin_();
  }
  // обновляем end, если удаляли
  if (m_end == nullptr) {
    EraceChangeEnd_();
  }
  --m_size;
  return true;
}

// сохраняет текущее дерево в файл в формате .dot

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::SaveTreeToDot(const std::string &file_name) {
  if (m_root != nullptr) {
    std::ofstream stream(file_name);
    if (stream.is_open()) {
      stream << "digraph {" << std::endl;
      if (m_size == 1) {
        stream << "  " << m_root->m_key_value.first << ";" << std::endl;
      } else {
        SaveTree_(m_root, &stream);
      }
      stream << "}";
      stream.close();
    }
  } else {
    std::ofstream stream(file_name);
    if (stream.is_open()) {
      stream << "";
      stream.close();
    }
  }
}

// рекурсивное копирование всех узлов дерева

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::CopyNode_(NodeTree<Key, Value> *current_node,
                                           NodeTree<Key, Value> *copy_node) {
  CopyNodeCharacteristics_(current_node, copy_node);
  //
  if (copy_node->m_node_right != nullptr) {
    current_node->m_node_right = new NodeTree<Key, Value>(
        copy_node->m_node_right->m_key_value, current_node, nullptr, nullptr);
    CopyNode_(current_node->m_node_right, copy_node->m_node_right);
  }
  //
  if (copy_node->m_node_left != nullptr) {
    current_node->m_node_left = new NodeTree<Key, Value>(
        copy_node->m_node_left->m_key_value, current_node, nullptr, nullptr);
    CopyNode_(current_node->m_node_left, copy_node->m_node_left);
  }
}

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::CopyNodeCharacteristics_(
    NodeTree<Key, Value> *current_node, const NodeTree<Key, Value> *copy_node) {
  // глубина левой ветки
  current_node->m_left_deep = copy_node->m_left_deep;
  // глубина правой ветки
  current_node->m_right_deep = copy_node->m_right_deep;
  // показатель балансировки
  current_node->m_bf = copy_node->m_bf;
}

// рекурсивное удаление всех узлов дерева

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::DeleteAllNodes_(NodeTree<Key, Value> *&node) {
  if (node != nullptr) {
    if (node->m_node_right != nullptr) {
      DeleteAllNodes_(node->m_node_right);
    }
    if (node->m_node_left != nullptr) {
      DeleteAllNodes_(node->m_node_left);
    }
    delete node;
    node = nullptr;
  }
}

// вспомогательные функции для insert

template <class Key, class Value>
typename AvlBalanceTree<Key, Value>::Iterator
AvlBalanceTree<Key, Value>::AddFirstElement_(
    const std::pair<Key, Value> &key_value) {
  m_root = new NodeTree<Key, Value>(key_value, nullptr, nullptr, nullptr);
  // создаем end
  NodeTree<Key, Value> *end =
      new NodeTree<Key, Value>(key_value, m_root, nullptr, nullptr);
  // связываем голову с end
  m_root->m_node_right = end;
  // сохраняем указатель на begin
  m_begin = m_root;
  // сохраняем указатель на end
  m_end = end;
  ++m_size;
  return Iterator(m_root);
}

template <class Key, class Value>
typename AvlBalanceTree<Key, Value>::Iterator
AvlBalanceTree<Key, Value>::AddOtherElement_(
    const std::pair<Key, Value> &key_value_insert,
    NodeTree<Key, Value> *current) {
  //
  Iterator result;
  //
  while (current != nullptr) {
    if (key_value_insert.first > current->m_key_value.first) {
      if (current->m_node_right == nullptr) {
        NodeTree<Key, Value> *insert_element = new NodeTree<Key, Value>(
            key_value_insert, nullptr, nullptr, nullptr);
        if (current == m_end) {
          current->m_node_parent->m_node_right = insert_element;
          insert_element->m_node_parent = current->m_node_parent;
          // удаляю старый end
          delete current;
          // создаю новый end
          NodeTree<Key, Value> *new_end = new NodeTree<Key, Value>(
              key_value_insert, insert_element, nullptr, nullptr);
          // связываю последний элемент с новым end
          insert_element->m_node_right = new_end;
          // сохраняем указатель новый end
          m_end = new_end;
        } else {
          insert_element->m_node_parent = current;
          current->m_node_right = insert_element;
        }
        BalanceTree_(insert_element);
        ++m_size;
        result = Iterator(insert_element);
        break;
      } else {
        current = current->m_node_right;
      }
    } else if (key_value_insert.first < current->m_key_value.first) {
      if (current->m_node_left == nullptr) {
        NodeTree<Key, Value> *insert_element = new NodeTree<Key, Value>(
            key_value_insert, current, nullptr, nullptr);
        current->m_node_left = insert_element;
        // сохраняем новый begin если это минимальный элемент
        if (current == m_begin) {
          m_begin = insert_element;
        }
        BalanceTree_(insert_element);
        ++m_size;
        result = Iterator(insert_element);
        break;
      } else {
        current = current->m_node_left;
      }
    } else {
      result = Iterator(current);
      break;
    }
  }
  //
  if (current == nullptr) {
    throw std::out_of_range("Error, in func add, current node is nullptr");
  }
  return result;
}

/*--- Функции для балансировки дерева ---*/ /*---AVL----*/

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::BalanceTree_(NodeTree<Key, Value> *cur_node) {
  while (cur_node != nullptr) {
    if (cur_node->m_node_left != nullptr) {
      cur_node->m_left_deep =
          cur_node->m_node_left->m_left_deep <
                  (cur_node->m_node_left->m_right_deep * -1)
              ? cur_node->m_node_left->m_left_deep - 1
              : (cur_node->m_node_left->m_right_deep * -1) - 1;
    } else {
      cur_node->m_left_deep = 0;
    }
    //
    if (cur_node->m_node_right != nullptr && cur_node->m_node_right != m_end) {
      cur_node->m_right_deep =
          cur_node->m_node_right->m_right_deep >
                  (cur_node->m_node_right->m_left_deep * -1)
              ? cur_node->m_node_right->m_right_deep + 1
              : (cur_node->m_node_right->m_left_deep * -1) + 1;
    } else {
      cur_node->m_right_deep = 0;
    }

    //
    cur_node->m_bf = cur_node->m_right_deep + cur_node->m_left_deep;
    //
    if (cur_node->m_bf == -2) {
      if (cur_node->m_node_left->m_bf <= 0) {
        SmallRightTurn_(cur_node);
      } else {
        BigRightTurn_(cur_node);
      }
    } else if (cur_node->m_bf == 2) {
      if (cur_node->m_node_right->m_bf >= 0) {
        SmallLeftTurn_(cur_node);
      } else {
        BigLeftTurn_(cur_node);
      }
    } else {
      cur_node = cur_node->m_node_parent;
    }
  }
}

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::SmallLeftTurn_(NodeTree<Key, Value> *current) {
  if (current->m_node_parent != nullptr) {
    if (current->m_node_parent->m_node_left == current) {
      current->m_node_parent->m_node_left = current->m_node_right;
    } else if (current->m_node_parent->m_node_right == current) {
      current->m_node_parent->m_node_right = current->m_node_right;
    }
  }
  NodeTree<Key, Value> *parentcurrent = current->m_node_parent;
  current->m_node_right->m_node_parent = current->m_node_parent;
  NodeTree<Key, Value> *timeBuf = current->m_node_right->m_node_left;
  current->m_node_right->m_node_left = current;

  current->m_node_parent = current->m_node_right;
  current->m_node_right = timeBuf;

  if (timeBuf != nullptr) {
    timeBuf->m_node_parent = current;
    timeBuf = nullptr;
  }
  if (parentcurrent == nullptr) {
    m_root = current->m_node_parent;
  }
  /////////
  AssignBalenceNode_(current);
  AssignBalenceNode_(current->m_node_parent);
  ////////
}

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::SmallRightTurn_(
    NodeTree<Key, Value> *current) {
  if (current->m_node_parent != nullptr) {
    if (current->m_node_parent->m_node_left == current) {
      current->m_node_parent->m_node_left = current->m_node_left;
    } else if (current->m_node_parent->m_node_right == current) {
      current->m_node_parent->m_node_right = current->m_node_left;
    }
  }
  NodeTree<Key, Value> *parentcurrent = current->m_node_parent;
  current->m_node_left->m_node_parent = current->m_node_parent;
  NodeTree<Key, Value> *timeBuf = current->m_node_left->m_node_right;
  current->m_node_left->m_node_right = current;

  current->m_node_parent = current->m_node_left;
  current->m_node_left = timeBuf;

  if (timeBuf != nullptr) {
    timeBuf->m_node_parent = current;
    timeBuf = nullptr;
  }
  if (parentcurrent == nullptr) {
    m_root = current->m_node_parent;
  }
  /////////
  AssignBalenceNode_(current);
  AssignBalenceNode_(current->m_node_parent);
  ////////
}

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::BigRightTurn_(NodeTree<Key, Value> *current) {
  if (current->m_node_parent != nullptr) {
    if (current->m_node_parent->m_node_left == current) {
      current->m_node_parent->m_node_left = current->m_node_left->m_node_right;
    } else if (current->m_node_parent->m_node_right == current) {
      current->m_node_parent->m_node_right = current->m_node_left->m_node_right;
    }
  }
  NodeTree<Key, Value> *ParentCur = current->m_node_parent;
  current->m_node_left->m_node_right->m_node_parent = current->m_node_parent;
  current->m_node_parent = current->m_node_left->m_node_right;

  NodeTree<Key, Value> *timeBuf1 =
      current->m_node_left->m_node_right->m_node_left;
  NodeTree<Key, Value> *timeBuf2 =
      current->m_node_left->m_node_right->m_node_right;

  current->m_node_left->m_node_right->m_node_left = current->m_node_left;
  current->m_node_left->m_node_right->m_node_right = current;

  current->m_node_left->m_node_parent = current->m_node_left->m_node_right;
  current->m_node_left->m_node_right = timeBuf1;
  if (timeBuf1 != nullptr) {
    timeBuf1->m_node_parent = current->m_node_left;
    timeBuf1 = nullptr;
  }
  current->m_node_left = timeBuf2;
  if (timeBuf2 != nullptr) {
    timeBuf2->m_node_parent = current;
    timeBuf2 = nullptr;
  }
  if (ParentCur == nullptr) {
    m_root = current->m_node_parent;
  }
  /////////
  AssignBalenceNode_(current);
  AssignBalenceNode_(current->m_node_parent);
  AssignBalenceNode_(current->m_node_parent->m_node_left);
  ////////
}

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::BigLeftTurn_(NodeTree<Key, Value> *current) {
  if (current->m_node_parent != nullptr) {
    if (current->m_node_parent->m_node_left == current) {
      current->m_node_parent->m_node_left = current->m_node_right->m_node_left;
    } else if (current->m_node_parent->m_node_right == current) {
      current->m_node_parent->m_node_right = current->m_node_right->m_node_left;
    }
  }
  NodeTree<Key, Value> *ParentCur = current->m_node_parent;
  current->m_node_right->m_node_left->m_node_parent = current->m_node_parent;
  current->m_node_parent = current->m_node_right->m_node_left;

  NodeTree<Key, Value> *timeBuf1 =
      current->m_node_right->m_node_left->m_node_left;
  NodeTree<Key, Value> *timeBuf2 =
      current->m_node_right->m_node_left->m_node_right;

  current->m_node_right->m_node_left->m_node_left = current;
  current->m_node_right->m_node_left->m_node_right = current->m_node_right;

  current->m_node_right->m_node_parent = current->m_node_right->m_node_left;
  current->m_node_right->m_node_left = timeBuf2;
  if (timeBuf2 != nullptr) {
    timeBuf2->m_node_parent = current->m_node_right;
    timeBuf2 = nullptr;
  }
  current->m_node_right = timeBuf1;
  if (timeBuf1 != nullptr) {
    timeBuf1->m_node_parent = current;
    timeBuf1 = nullptr;
  }
  if (ParentCur == nullptr) {
    m_root = current->m_node_parent;
  }
  /////////
  AssignBalenceNode_(current);
  AssignBalenceNode_(current->m_node_parent);
  AssignBalenceNode_(current->m_node_parent->m_node_right);
  ////////
}

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::AssignBalenceNode_(
    NodeTree<Key, Value> *current) {
  if (current->m_node_left != nullptr) {
    current->m_left_deep = MaxDepthNodeTree_(current->m_node_left) * -1 - 1;
  } else {
    current->m_left_deep = 0;
  }
  if (current->m_node_right != nullptr) {
    current->m_right_deep = MaxDepthNodeTree_(current->m_node_right) + 1;
  } else {
    current->m_right_deep = 0;
  }
  current->m_bf = current->m_left_deep + current->m_right_deep;
}

template <class Key, class Value>
int AvlBalanceTree<Key, Value>::MaxDepthNodeTree_(
    NodeTree<Key, Value> *current) {
  if (current == nullptr) {
    return (-1);  // an empty tree  has height −1
  } else {
    // compute the depth of each subtree
    int leftDepth = MaxDepthNodeTree_(current->m_node_left);
    int rightDepth = MaxDepthNodeTree_(current->m_node_right);
    // use the larger one
    if (leftDepth > rightDepth) {
      return (leftDepth + 1);
    } else {
      return (rightDepth + 1);
    }
  }
}

// вспомогательная функция для удаления элемента из дерева

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::EraceChangeBegin_() {
  // если удаляем минимальный элемент в дереве, то меняем begin
  if (m_root != nullptr) {
    m_begin = m_root;
    while (m_begin->m_node_left != nullptr) {
      m_begin = m_begin->m_node_left;
    }
  }
}

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::EraceChangeEnd_() {
  if (m_root != nullptr) {
    NodeTree<Key, Value> *cur = m_root;
    while (cur->m_node_right != nullptr) {
      cur = cur->m_node_right;
    }
    // создаю новый end
    NodeTree<Key, Value> *new_end =
        new NodeTree<Key, Value>(cur->m_key_value, cur, nullptr, nullptr);
    // связываю последний элемент с новым end
    cur->m_node_right = new_end;
    // сохраняем указатель новый end
    m_end = new_end;
  }
}

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::EraceWithoutKids_(
    NodeTree<Key, Value> *delete_node) {
  //
  if (delete_node->m_node_parent->m_node_right == delete_node) {
    // если элемент является правым потомком родителя
    delete_node->m_node_parent->m_node_right = nullptr;
  } else {
    // если элемент является левым потомком родителя
    delete_node->m_node_parent->m_node_left = nullptr;
  }

  BalanceTree_(delete_node->m_node_parent);

  delete delete_node;
}

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::EraceWithOneKid_(
    NodeTree<Key, Value> *delete_node) {
  //
  NodeTree<Key, Value> *position_kid;
  if (delete_node->m_node_right != nullptr) {
    // если есть правый потомок
    position_kid = delete_node->m_node_right;
  } else {
    // если есть левый потомок
    position_kid = delete_node->m_node_left;
  }

  if (delete_node->m_node_parent->m_node_right == delete_node) {
    // если элемент является правым потомком родителя
    delete_node->m_node_parent->m_node_right = position_kid;
  } else {
    // если элемент является левым потомком родителя
    delete_node->m_node_parent->m_node_left = position_kid;
  }
  // меняем родителя в наследнике на родителя удаляемого элемента
  position_kid->m_node_parent = delete_node->m_node_parent;
  //
  BalanceTree_(position_kid);
  delete delete_node;
}

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::EraceWithTwoKids_(
    NodeTree<Key, Value> *delete_node) {
  //

  NodeTree<Key, Value> *buffer_right = delete_node->m_node_right;

  if (buffer_right->m_node_left != nullptr) {
    while (buffer_right->m_node_left != nullptr) {
      buffer_right = buffer_right->m_node_left;
    }
    NodeTree<Key, Value> *buf = buffer_right->m_node_right;

    buffer_right->m_node_parent->m_node_left = buf;
    if (buf != nullptr) {
      buf->m_node_parent = buffer_right->m_node_parent;
    }
    BalanceTree_(buffer_right->m_node_parent);
    //
    buffer_right->m_node_right = delete_node->m_node_right;
    delete_node->m_node_right->m_node_parent = buffer_right;
  }

  if (delete_node->m_node_parent->m_node_right == delete_node) {
    delete_node->m_node_parent->m_node_right = buffer_right;
  } else {
    delete_node->m_node_parent->m_node_left = buffer_right;
  }
  buffer_right->m_node_parent = delete_node->m_node_parent;

  buffer_right->m_node_left = delete_node->m_node_left;
  if (delete_node->m_node_left != nullptr) {
    delete_node->m_node_left->m_node_parent = buffer_right;
  }
  BalanceTree_(buffer_right);
  delete delete_node;
}

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::EraceRoot_(NodeTree<Key, Value> *delete_node) {
  if (delete_node->m_node_right != nullptr &&
      delete_node->m_node_left == nullptr) {
    m_root = delete_node->m_node_right;
    m_root->m_node_parent = nullptr;
    BalanceTree_(m_root);
  } else if (delete_node->m_node_left != nullptr &&
             delete_node->m_node_right == nullptr) {
    m_root = delete_node->m_node_left;
    m_root->m_node_parent = nullptr;
    BalanceTree_(m_root);
  } else if (delete_node->m_node_right != nullptr &&
             delete_node->m_node_left != nullptr) {
    NodeTree<Key, Value> *buffer = delete_node->m_node_right;
    if (buffer->m_node_left != nullptr) {
      while (buffer->m_node_left != nullptr) {
        buffer = buffer->m_node_left;
      }
      NodeTree<Key, Value> *buffer_right = buffer->m_node_right;

      buffer->m_node_parent->m_node_left = buffer_right;
      if (buffer_right != nullptr) {
        buffer_right->m_node_parent = buffer->m_node_parent;
      }
      BalanceTree_(buffer->m_node_parent);

      buffer->m_node_right = delete_node->m_node_right;
      delete_node->m_node_right->m_node_parent = buffer;
    }
    buffer->m_node_left = delete_node->m_node_left;
    if (delete_node->m_node_left != nullptr) {
      delete_node->m_node_left->m_node_parent = buffer;
    }
    buffer->m_node_parent = nullptr;
    m_root = buffer;
    BalanceTree_(m_root);

  } else {
    m_root = nullptr;
  }
  delete delete_node;
}

template <class Key, class Value>
void AvlBalanceTree<Key, Value>::SaveTree_(NodeTree<Key, Value> *node,
                                           std::ofstream *stream) {
  if (node->m_node_left != nullptr) {
    *stream << "  " << node->m_key_value.first << " -> "
            << node->m_node_left->m_key_value.first
            << " [label = " << node->m_left_deep << "];" << std::endl;
    SaveTree_(node->m_node_left, stream);
  }
  //
  if (node->m_node_right != nullptr && node->m_node_right != m_end) {
    *stream << "  " << node->m_key_value.first << " -> "
            << node->m_node_right->m_key_value.first
            << " [label = " << node->m_right_deep << "];" << std::endl;
    SaveTree_(node->m_node_right, stream);
  }
}
