#ifndef SRC_CONTROLLER_HPP_
#define SRC_CONTROLLER_HPP_

#include <random>

#include "hash_table.hpp"
#include "self_balancing_binary_search_tree.hpp"
#include "student_record.hpp"

class Controller {
 public:
  typedef HashTable<std::string, StudentRecord> hash_t;
  typedef SelfBalancingBinarySearchTree<std::string, StudentRecord> binary_tree;
  typedef AbstractStructDatabase<std::string, StudentRecord> data_base;

  enum BaseRealisation { kHashTable, kBinaryTree };

  Controller(bool base_realisation = kHashTable);
  Controller(const Controller &other);
  Controller(Controller &&other);
  ~Controller();

  void operator=(const Controller &other);
  void operator=(Controller &&other);

  std::pair<std::string, bool> Set(const std::string &key,
                                   const StudentRecord &record,
                                   const int seconds = 0);
  std::pair<std::string, bool> Get(const std::string &key);
  std::pair<std::string, bool> Exist(const std::string &key);
  std::pair<std::string, bool> Del(const std::string &key);
  std::pair<std::string, bool> Update(const std::string &key,
                                      const StudentRecord &value);
  std::pair<std::string, bool> Keys();
  std::pair<std::string, bool> Rename(const std::string &old_key,
                                      const std::string &cur_key);
  std::pair<std::string, bool> Ttl(const std::string &key);
  std::pair<std::string, bool> Find(const StudentRecord &search_value);
  std::pair<std::vector<StudentRecord>, bool> ShowAll();
  std::pair<std::string, bool> Upload(const std::string &file_name);
  std::pair<std::string, bool> Export(const std::string &file_name);

 private:
  bool m_base_type{};
  data_base *m_model;
};

#endif  // SRC_CONTROLLER_HPP_
