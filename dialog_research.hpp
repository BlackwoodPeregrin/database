#ifndef SRC_DIALOG_RESEARCH_HPP_
#define SRC_DIALOG_RESEARCH_HPP_

#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

#include "colors.hpp"
#include "controller.hpp"

class DialogResearch {
 public:
  void Show();

 protected:
  void PrintMainMenu_();
  void ScanfInput_();
  void StartTest_();

  int ProtectedInput_();
  void InstallSumItems_();
  void InstallSumActions_();
  void PauseFunc_();
  void ColorPrint_(const std::string &message, const std::string &color_start,
                   const std::string &color_end);

 private:
  /* ============== Tests =================== */
  std::pair<double, double> TestGetElement_(
      const std::vector<std::pair<std::string, StudentRecord>> &key_value);
  std::pair<double, double> TestAddElement_();
  std::pair<double, double> TestGetAllElements_();
  std::pair<double, double> TestFindKey_(
      const std::vector<std::pair<std::string, StudentRecord>> &key_value);
  std::pair<double, double> TestDeleteElement_(
      const std::vector<std::pair<std::string, StudentRecord>> &key_value);

  /* =========== Random Generator =========== */
  std::string GenerateKey_();
  StudentRecord GenerateStructStudent_();
  int GetRandom(int left_limit, int right_limit);

 private:
  const double kMicroToMs = 0.001;

  colors color{};
  bool m_draw{true};
  bool m_exit{false};

  size_t m_sum_items{0};
  size_t m_sum_actions{0};

  Controller *m_conroller1{};
  Controller *m_conroller2{};
};

#endif  // SRC_DIALOG_RESEARCH_HPP_
