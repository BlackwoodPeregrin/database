#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_

#include <string>

#include "dialog_database.hpp"
#include "dialog_research.hpp"

class MainWindow {
 public:
  MainWindow();
  MainWindow(const MainWindow &other);
  MainWindow(MainWindow &&other);
  ~MainWindow();

  void operator=(const MainWindow &other);
  void operator=(MainWindow &&other);

  void Show();

 private:
  void MainInput();
  std::string ProtectedInput();
  void PrintMainMenu();

 private:
  colors color;
  bool exit_{false};
  bool draw_{true};
};

#endif  // SRC_MAINWINDOW_H_
