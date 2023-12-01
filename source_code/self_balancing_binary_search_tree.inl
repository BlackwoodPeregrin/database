#include <ctime>
#include <fstream>

template <class Key, class Value>
SelfBalancingBinarySearchTree<Key, Value>::SelfBalancingBinarySearchTree()
    : AvlBalanceTree<Key, Value>() {}

template <class Key, class Value>
SelfBalancingBinarySearchTree<Key, Value>::SelfBalancingBinarySearchTree(
    const SelfBalancingBinarySearchTree &other)
    : AvlBalanceTree<Key, Value>(other) {}

template <class Key, class Value>
SelfBalancingBinarySearchTree<Key, Value>::SelfBalancingBinarySearchTree(
    SelfBalancingBinarySearchTree &&other)
    : AvlBalanceTree<Key, Value>(std::move(other)) {}

template <class Key, class Value>
SelfBalancingBinarySearchTree<Key, Value>::~SelfBalancingBinarySearchTree() {}

template <class Key, class Value>
SelfBalancingBinarySearchTree<Key, Value>
    &SelfBalancingBinarySearchTree<Key, Value>::operator=(
        const SelfBalancingBinarySearchTree &other) {
  AvlBalanceTree<Key, Value>::operator=(other);
  return *this;
}

template <class Key, class Value>
SelfBalancingBinarySearchTree<Key, Value>
    &SelfBalancingBinarySearchTree<Key, Value>::operator=(
        SelfBalancingBinarySearchTree &&other) {
  AvlBalanceTree<Key, Value>::operator=(std::move(other));
  return *this;
}

/* ======================== Override =========================== */

template <class Key, class Value>
bool SelfBalancingBinarySearchTree<Key, Value>::SET(const Key &key,
                                                    const Value &value,
                                                    const size_t &life_time) {
  if (IsElementTimeEnd_(key) == -1) {
    this->Erase(key);
  }
  bool result = this->Insert(key, value).second;
  if (result == true && life_time != 0) {
    m_look_up.push_back({key, time(0) + life_time});
  }
  return result;
}

template <class Key, class Value>
Value SelfBalancingBinarySearchTree<Key, Value>::GET(const Key &key) {
  auto iter = this->Find(key);
  if (iter == this->end() || IsElementTimeEnd_(key) == -1) {
    throw std::out_of_range("(null)");
  }
  return (*iter).second;
}

template <class Key, class Value>
bool SelfBalancingBinarySearchTree<Key, Value>::EXIST(const Key &key) {
  if (IsElementTimeEnd_(key) == -1) {
    this->Erase(key);
  }
  return this->Contains(key);
}

template <class Key, class Value>
bool SelfBalancingBinarySearchTree<Key, Value>::DEL(const Key &key) {
  if (IsElementTimeEnd_(key) == -1) {
    return this->Erase(key);
  }
  return this->Erase(key);
}

template <class Key, class Value>
bool SelfBalancingBinarySearchTree<Key, Value>::UPDATE(const Key &key,
                                                       const Value &value) {
  if (IsElementTimeEnd_(key) == -1) {
    this->Erase(key);
  }
  auto iter = this->Find(key);
  if (iter != this->end()) {
    (*iter).second = value;
    return true;
  }
  return false;
}

template <class Key, class Value>
std::vector<Key> SelfBalancingBinarySearchTree<Key, Value>::KEYS() {
  std::vector<Key> keys;
  std::vector<Key> del_keys;
  for (auto iter = this->begin(); iter != this->end(); ++iter) {
    Key key = (*iter).first;
    if (IsElementTimeEnd_(key) == -1) {
      del_keys.push_back(key);
    } else {
      keys.push_back(key);
    }
  }
  for (size_t i = 0; i < del_keys.size(); ++i) {
    this->Erase(del_keys[i]);
  }
  return keys;
}

template <class Key, class Value>
bool SelfBalancingBinarySearchTree<Key, Value>::RENAME(
    const Key &old_name_key, const Key &cur_name_key) {
  if (IsElementTimeEnd_(old_name_key) == -1) {
    this->Erase(old_name_key);
  }
  if (IsElementTimeEnd_(cur_name_key) == -1) {
    this->Erase(cur_name_key);
  }
  auto search_old_key = this->Find(old_name_key);
  auto search_cur_key = this->Find(cur_name_key);
  if (search_old_key != this->end() && search_cur_key == this->end()) {
    int time_life = IsElementTimeEnd_(old_name_key);
    Value tmp_value = (*search_old_key).second;
    SET(cur_name_key, tmp_value, time_life);
    this->Erase(old_name_key);
    for (auto iter{m_look_up.begin()}; iter != m_look_up.end(); ++iter) {
      if ((*iter).first == old_name_key) {
        m_look_up.erase(iter);
        break;
      }
    }
    return true;
  }
  return false;
}

template <class Key, class Value>
int SelfBalancingBinarySearchTree<Key, Value>::TTL(const Key &key) {
  int result = IsElementTimeEnd_(key);
  if (result == -1) {
    this->Erase(key);
    throw std::out_of_range("(null)");
  } else if (result == 0) {
    if (this->Find(key) == this->end()) {
      throw std::out_of_range("(null)");
    }
    throw std::out_of_range("(inf)");
  }
  return result;
}

template <class Key, class Value>
std::vector<Key> SelfBalancingBinarySearchTree<Key, Value>::FIND(
    const Value &search_value) {
  std::vector<Key> keys;
  std::vector<Key> del_keys;
  for (auto iter = this->begin(); iter != this->end(); ++iter) {
    if (IsElementTimeEnd_((*iter).first) == -1) {
      del_keys.push_back((*iter).first);
    } else {
      if ((*iter).second == search_value) {
        keys.push_back((*iter).first);
      }
    }
  }
  for (size_t i = 0; i < del_keys.size(); ++i) {
    this->Erase(del_keys[i]);
  }
  return keys;
}

template <class Key, class Value>
std::vector<Value> SelfBalancingBinarySearchTree<Key, Value>::SHOWALL() {
  std::vector<Value> values;
  std::vector<Key> del_keys;
  for (auto iter = this->begin(); iter != this->end(); ++iter) {
    if (IsElementTimeEnd_((*iter).first) == -1) {
      del_keys.push_back((*iter).first);
    } else {
      values.push_back((*iter).second);
    }
  }
  for (size_t i = 0; i < del_keys.size(); ++i) {
    this->Erase(del_keys[i]);
  }
  return values;
}

template <class Key, class Value>
int SelfBalancingBinarySearchTree<Key, Value>::UPLOAD(
    const std::string &file_name) {
  int res{};
  std::ifstream stream(file_name);
  if (stream.is_open()) {
    Key key{};
    Value record{};
    setlocale(LC_ALL, "en_US.UTF-8");
    while (!stream.eof()) {
      stream >> key;
      if (!stream.eof()) {
        stream >> record;
        SET(key, record);
        res++;
      }
    }
  } else {
    throw std::invalid_argument("No such file.");
  }

  return res;
}

template <class Key, class Value>
int SelfBalancingBinarySearchTree<Key, Value>::EXPORT(
    const std::string &file_name) {
  std::ofstream stream(file_name);
  if (stream.is_open()) {
    int tmp = 0;
    for (auto iter = this->begin(); iter != this->end(); ++iter) {
      stream << (*iter).first << " " << (*iter).second << std::endl;
      ++tmp;
    }
    stream.close();
    return tmp;
  } else {
    throw std::invalid_argument("No such file.");
  }
}

/* ============================================================ */

template <class Key, class Value>
int SelfBalancingBinarySearchTree<Key, Value>::IsElementTimeEnd_(
    const Key &key) {
  size_t time_now = time(0);
  for (auto iter = m_look_up.begin(); iter != m_look_up.end(); ++iter) {
    if ((*iter).first == key) {
      if ((*iter).second <= time_now) {
        m_look_up.erase(iter);
        return -1;
      } else {
        return (*iter).second - time_now;
      }
    }
  }
  return 0;
}
