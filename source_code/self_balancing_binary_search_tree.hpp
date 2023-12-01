#ifndef SRC_SELF_BALANCING_BINARY_SEARCH_TREE_HPP_
#define SRC_SELF_BALANCING_BINARY_SEARCH_TREE_HPP_

#include <utility>
#include <vector>

#include "abstract_struct_data_base.hpp"
#include "balance_tree/avlTree.hpp"

template <class Key, class Value>
class SelfBalancingBinarySearchTree
    : public AvlBalanceTree<Key, Value>,
      public AbstractStructDatabase<Key, Value> {
 public:
  SelfBalancingBinarySearchTree();
  SelfBalancingBinarySearchTree(const SelfBalancingBinarySearchTree &other);
  SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree &&other);
  ~SelfBalancingBinarySearchTree();
  //
  SelfBalancingBinarySearchTree &operator=(
      const SelfBalancingBinarySearchTree &other);
  //
  SelfBalancingBinarySearchTree &operator=(
      SelfBalancingBinarySearchTree &&other);
  //

  /* ======================== Override =========================== */

  bool SET(const Key &key, const Value &value,
           const size_t &life_time = 0) override;
  Value GET(const Key &key) override;
  bool EXIST(const Key &key) override;
  bool DEL(const Key &key) override;
  bool UPDATE(const Key &key, const Value &value) override;
  std::vector<Key> KEYS() override;
  bool RENAME(const Key &old_name_key, const Key &cur_name_key) override;
  int TTL(const Key &key) override;
  std::vector<Key> FIND(const Value &search_value) override;
  std::vector<Value> SHOWALL() override;
  int UPLOAD(const std::string &file_name) override;
  int EXPORT(const std::string &file_name) override;

  /* ============================================================ */

 protected:
  int IsElementTimeEnd_(const Key &key);
  std::vector<std::pair<Key, size_t>> m_look_up;
};

#include "self_balancing_binary_search_tree.inl"

#endif  // SRC_SELF_BALANCING_BINARY_SEARCH_TREE_HPP_
