#ifndef SRC_DIALOGDATABASE_HPP_
#define SRC_DIALOGDATABASE_HPP_

#include <string>

#include "colors.hpp"
#include "controller.hpp"

class DialogDataBase {
 public:
  DialogDataBase(bool db_type = Controller::kHashTable);
  DialogDataBase(const DialogDataBase &other);
  DialogDataBase(DialogDataBase &&other);
  ~DialogDataBase();

  void operator=(const DialogDataBase &other);
  void operator=(DialogDataBase &&other);

  void Show();

 private:
  void ScanInput();
  std::string ProtectedInput();

  void PrintHeader();
  void Unrecognized();
  void PrintHelp();
  void ClearScreen();

  void SlotSet();
  void SlotGet();
  void SlotExist();
  void SlotDel();
  void SlotUpdate();
  void SlotKeys();
  void SlotRename();
  void SlotTtl();
  void SlotFind();
  void SlotShowAll();
  void SlotUpload();
  void SlotExport();

 private:
  colors color;
  bool db_type_;
  bool exit_{false};
  bool draw_{true};
  Controller *controller_;
};

#endif  // SRC_DIALOGDATABASE_HPP_
