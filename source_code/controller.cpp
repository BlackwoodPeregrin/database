#include "controller.hpp"

#include <vector>

Controller::Controller(bool base_realisation) {
  if (base_realisation == BaseRealisation::kHashTable) {
    m_model = new hash_t;
  } else {
    m_model = new binary_tree;
  }
  m_base_type = base_realisation;
}

Controller::Controller(const Controller &other) : m_model(nullptr) {
  *this = other;
}

Controller::Controller(Controller &&other) : m_model(nullptr) {
  *this = std::move(other);
}

Controller::~Controller() { delete m_model; }

void Controller::operator=(const Controller &other) {
  if (this != &other) {
    delete m_model;
    m_model = nullptr;
    if (other.m_model != nullptr) {
      if (other.m_base_type == BaseRealisation::kHashTable) {
        m_model = new hash_t;
      } else {
        m_model = new binary_tree;
      }
      m_base_type = other.m_base_type;
    }
  }
}

void Controller::operator=(Controller &&other) {
  delete m_model;
  m_model = nullptr;
  std::swap(m_model, other.m_model);
  std::swap(m_base_type, other.m_base_type);
}

std::pair<std::string, bool> Controller::Set(const std::string &key,
                                             const StudentRecord &record,
                                             const int seconds) {
  std::pair<std::string, bool> res{};
  if (seconds < 0) {
    res = {"expiration time must be greater than 0", false};
  } else {
    try {
      res = {(m_model->SET(key, record, seconds)) ? "OK" : "Key is occupied",
             true};
    } catch (const std::exception &e) {
      res = {e.what(), false};
    }
  }
  return res;
}

std::pair<std::string, bool> Controller::Get(const std::string &key) {
  std::pair<std::string, bool> result{};
  try {
    StudentRecord value = m_model->GET(key);
    result = {value.ToString(), true};
  } catch (const std::exception &e) {
    result = {e.what(), false};
  }
  return result;
}

std::pair<std::string, bool> Controller::Exist(const std::string &key) {
  return {(m_model->EXIST(key)) ? "True" : "False", true};
}

std::pair<std::string, bool> Controller::Del(const std::string &key) {
  return {(m_model->DEL(key)) ? "OK" : "FAIL", true};
}

std::pair<std::string, bool> Controller::Update(const std::string &key,
                                                const StudentRecord &value) {
  return {(m_model->UPDATE(key, value)) ? "OK" : "FAIL", true};
}

std::pair<std::string, bool> Controller::Keys() {
  std::pair<std::string, bool> result{};
  try {
    std::vector<std::string> key(std::move(m_model->KEYS()));
    for (size_t i = 0; i < key.size(); i++) {
      result.first += std::to_string(i + 1) + ") " + key[i];
      if (i != key.size() - 1) {
        result.first += "\n";
      }
    }
    if (result.first.empty()) result.first = "Database is empty.";
    result.second = true;
  } catch (const std::exception &e) {
    result = {e.what(), false};
  }
  return result;
}

std::pair<std::string, bool> Controller::Rename(const std::string &old_key,
                                                const std::string &cur_key) {
  std::pair<std::string, bool> res{};
  try {
    res = {m_model->RENAME(old_key, cur_key) ? "OK" : "FAIL", true};
  } catch (const std::exception &e) {
    res = {e.what(), false};
  }
  return res;
}

std::pair<std::string, bool> Controller::Ttl(const std::string &key) {
  std::pair<std::string, bool> result{};
  try {
    result = {std::to_string(m_model->TTL(key)), true};
  } catch (const std::exception &e) {
    result = {e.what(), false};
  }
  return result;
}

std::pair<std::string, bool> Controller::Find(
    const StudentRecord &search_value) {
  std::pair<std::string, bool> result{};
  try {
    std::vector<std::string> key(std::move(m_model->FIND(search_value)));
    if (key.size()) {
      for (size_t i = 0; i < key.size(); i++) {
        result.first.append(std::to_string(i + 1) + ") " + key[i]);
        if (i != key.size() - 1) {
          result.first += "\n";
        }
      }
      result.second = true;
    } else {
      result = {"No matches found", false};
    }
  } catch (const std::exception &e) {
    result = {e.what(), false};
  }
  return result;
}

std::pair<std::vector<StudentRecord>, bool> Controller::ShowAll() {
  std::pair<std::vector<StudentRecord>, bool> res{};
  try {
    res = {m_model->SHOWALL(), true};
  } catch (const std::exception &e) {
    res.second = false;
  }
  return res;
}

std::pair<std::string, bool> Controller::Upload(const std::string &file_name) {
  std::pair<std::string, bool> res{};
  try {
    res = {"OK " + std::to_string(m_model->UPLOAD(file_name)), true};
  } catch (const std::exception &e) {
    res = {e.what(), false};
  }
  return res;
}

std::pair<std::string, bool> Controller::Export(const std::string &file_name) {
  std::pair<std::string, bool> res{};
  try {
    res = {"OK " + std::to_string(m_model->EXPORT(file_name)), true};
  } catch (const std::exception &e) {
    res = {e.what(), false};
  }
  return res;
}
