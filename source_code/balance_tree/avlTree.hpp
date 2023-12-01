#pragma once

#include <iostream>

#include "treeIterator.hpp"

template <class Key, class Value>
class AvlBalanceTree {
 public:
  AvlBalanceTree();
  AvlBalanceTree(const AvlBalanceTree &other);
  explicit AvlBalanceTree(const std::initializer_list<std::pair<Key, Value>> &items);
  AvlBalanceTree(AvlBalanceTree &&other);
  ~AvlBalanceTree();

  AvlBalanceTree &operator=(const AvlBalanceTree &other);
  AvlBalanceTree &operator=(AvlBalanceTree &&other);

  void Clear();
  size_t Size();
  bool IsEmpty();

  /* =================== Class Iterator ===================== */
 public:
  class Iterator : public TreeIterator<Key, Value> {
   public:
    Iterator();
    Iterator(const Iterator &other);
    explicit Iterator(NodeTree<Key, Value> *node);
    Iterator(Iterator &&other);
    ~Iterator();

    Iterator &operator=(const Iterator &other);
    Iterator &operator=(Iterator &&other);

    bool operator!=(const Iterator &other);
    bool operator==(const Iterator &other);
  };
  /* ======================================================== */

 public:
  Iterator begin();
  Iterator end();

  /* ================= Class Const Iterator ================= */
 public:
  class ConstIterator : public Iterator {
   public:
    ConstIterator();
    ConstIterator(const ConstIterator &other);
    explicit ConstIterator(NodeTree<Key, Value> *node);
    ConstIterator(ConstIterator &&other);
    ~ConstIterator();

    ConstIterator &operator=(const ConstIterator &other);
    ConstIterator &operator=(ConstIterator &&other);

    bool operator!=(const ConstIterator &other);
    bool operator==(const ConstIterator &other);

    const std::pair<const Key, Value> &operator*();
  };
  /* ======================================================== */

 public:
  ConstIterator cbegin();
  ConstIterator cend();

 public:
  bool Contains(const Key &key);
  Iterator Find(const Key &key);

  std::pair<Iterator, bool> Insert(const std::pair<Key, Value> &pair);
  std::pair<Iterator, bool> Insert(const Key &key, const Value &value);

  bool Erase(Iterator pos);
  bool Erase(const Key &key);

  // сохраняет текущее дерево в файл в формате .dot
  void SaveTreeToDot(const std::string &file_name);

 protected:
  // рекурсивное копирование всех узлов дерева
  void CopyNode_(NodeTree<Key, Value> *current_node,
                 NodeTree<Key, Value> *copy_node);

  void CopyNodeCharacteristics_(NodeTree<Key, Value> *current_node,
                                const NodeTree<Key, Value> *copy_node);

  // рекурсивное удаление всех узлов дерева
  void DeleteAllNodes_(NodeTree<Key, Value> *&node);

  // вспомогательные функции для insert
  Iterator AddFirstElement_(const std::pair<Key, Value> &key_value);
  Iterator AddOtherElement_(const std::pair<Key, Value> &key_value_insert,
                            NodeTree<Key, Value> *current);

  /*--- Функции для балансировки дерева ---*/ /*---AVL----*/
  void BalanceTree_(NodeTree<Key, Value> *cur_node);
  void SmallLeftTurn_(NodeTree<Key, Value> *current);
  void SmallRightTurn_(NodeTree<Key, Value> *current);
  void BigRightTurn_(NodeTree<Key, Value> *Current);
  void BigLeftTurn_(NodeTree<Key, Value> *Current);
  void AssignBalenceNode_(NodeTree<Key, Value> *current);
  int MaxDepthNodeTree_(NodeTree<Key, Value> *current);

  // вспомогательная функция для удаления элемента из дерева
  void EraceChangeBegin_();
  void EraceChangeEnd_();
  void EraceWithoutKids_(NodeTree<Key, Value> *delete_node);
  void EraceWithOneKid_(NodeTree<Key, Value> *delete_node);
  void EraceWithTwoKids_(NodeTree<Key, Value> *delete_node);
  void EraceRoot_(NodeTree<Key, Value> *delete_node);

  // вспомогательная функция для сохранения текущего дерева в файл
  void SaveTree_(NodeTree<Key, Value> *node, std::ofstream *stream);

 protected:
  NodeTree<Key, Value> *m_root;
  NodeTree<Key, Value> *m_begin;
  NodeTree<Key, Value> *m_end;
  size_t m_size;
};

#include "avlTree.inl"
