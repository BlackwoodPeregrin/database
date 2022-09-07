#include "main_window.hpp"

#include <algorithm>
#include <iostream>

MainWindow::MainWindow() {}

MainWindow::MainWindow(const MainWindow &other) { *this = other; }

MainWindow::MainWindow(MainWindow &&other) { *this = std::move(other); }

MainWindow::~MainWindow() {}

void MainWindow::operator=(const MainWindow &other) {
  if (this != &other) {
    exit_ = other.exit_;
    draw_ = other.draw_;
  }
}

void MainWindow::operator=(MainWindow &&other) {
  if (this != &other) {
    std::swap(exit_, other.exit_);
    std::swap(draw_, other.draw_);
  }
}

void MainWindow::Show() {
  while (!exit_) {
    if (draw_) {
      PrintMainMenu();
      draw_ = false;
    }
    MainInput();
  }
}

void MainWindow::MainInput() {
  std::string choose = ProtectedInput();
  if (choose == "1") {
    DialogDataBase dialog(Controller::kHashTable);
    dialog.Show();
  } else if (choose == "2") {
    DialogDataBase dialog(Controller::kBinaryTree);
    dialog.Show();
  } else if (choose == "3") {
    DialogResearch dialog;
    dialog.Show();
  } else if (choose == "4") {
    exit_ = true;
  }
  draw_ = true;
}

std::string MainWindow::ProtectedInput() {
  std::string res{};
  std::cout << color.yellow;
  std::cin >> res;
  std::cout << color.end;
  if (std::cin.eof()) {
    exit(0);
  }
  return res;
}

void MainWindow::PrintMainMenu() {
  system("clear");
  std::cout << color.blue << " === Project Database ===\n";
  std::cout << color.white << "1 - Hash Table\n";
  std::cout << "2 - Self Balancing Binary Search Tree\n";
  std::cout << "3 - Research\n";
  std::cout << "4 - Exit" << color.end << std::endl;
}
