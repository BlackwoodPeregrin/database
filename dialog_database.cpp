#include "dialog_database.hpp"

#include <algorithm>
#include <iostream>

DialogDataBase::DialogDataBase(bool db_type)
    : controller_(new Controller(db_type)) {
  db_type_ = db_type;
}

DialogDataBase::DialogDataBase(const DialogDataBase &other)
    : controller_(new Controller) {
  *this = other;
}

DialogDataBase::DialogDataBase(DialogDataBase &&other)
    : controller_(new Controller) {
  *this = std::move(other);
}

DialogDataBase::~DialogDataBase() { delete controller_; }

void DialogDataBase::operator=(const DialogDataBase &other) {
  if (this != &other) {
    db_type_ = other.db_type_;
    exit_ = other.exit_;
    draw_ = other.draw_;
    *controller_ = *other.controller_;
  }
}

void DialogDataBase::operator=(DialogDataBase &&other) {
  if (this != &other) {
    std::swap(db_type_, other.db_type_);
    std::swap(exit_, other.exit_);
    std::swap(draw_, other.draw_);
    std::swap(controller_, other.controller_);
  }
}

void DialogDataBase::Show() {
  ClearScreen();
  while (!exit_) {
    if (draw_) {
      PrintHeader();
      draw_ = false;
    }
    ScanInput();
  }
}

void DialogDataBase::ScanInput() {
  std::string choose = ProtectedInput();
  std::cout << color.end;
  std::transform(choose.begin(), choose.end(), choose.begin(), ::toupper);
  if (choose == "SET") {
    std::cout << color.blue;
    SlotSet();
    std::cout << color.end;
  } else if (choose == "GET") {
    SlotGet();
  } else if (choose == "EXIST") {
    SlotExist();
  } else if (choose == "DEL") {
    SlotDel();
  } else if (choose == "UPDATE") {
    SlotUpdate();
  } else if (choose == "KEYS") {
    SlotKeys();
  } else if (choose == "RENAME") {
    SlotRename();
  } else if (choose == "TTL") {
    SlotTtl();
  } else if (choose == "FIND") {
    SlotFind();
    std::cout << color.end;
  } else if (choose == "SHOWALL") {
    SlotShowAll();
  } else if (choose == "UPLOAD") {
    SlotUpload();
  } else if (choose == "EXPORT") {
    SlotExport();
  } else if (choose == "HELP") {
    PrintHelp();
  } else if (choose == "CLEAR") {
    ClearScreen();
  } else if (choose == "Q") {
    exit_ = true;
  } else {
    Unrecognized();
  }
}

std::string DialogDataBase::ProtectedInput() {
  std::cout << color.blue;
  std::string res{};
  std::cin >> res;
  if (std::cin.eof()) exit(0);
  return res;
}

void DialogDataBase::PrintHeader() {
  std::cout << color.pink;
  if (db_type_ == Controller::kHashTable)
    std::cout << " --- Hash Table Data Base ---" << std::endl;
  else
    std::cout << " ---    Tree Data Base    ---" << std::endl;
  draw_ = false;
  std::cout << color.end;
}

void DialogDataBase::Unrecognized() {
  std::cout.flush();
  std::cin.clear();
  std::cout << color.green << "Input unrecognized, type 'help' for help"
            << color.end << std::endl;
}

void DialogDataBase::PrintHelp() {
  std::cout.flush();
  std::cin.clear();
  std::cout << color.white << "Available commands and syntax:\n";
  std::cout << color.pink << "SET\t" << color.white
            << ": SET key last_name first_name year city coins\n";
  std::cout << "\tor SET key last_name first_name year city coins EX "
               "seconds\t- add new entry\n";
  std::cout << color.pink << "GET\t" << color.white
            << ": GET key\t- get asociated value\n";
  std::cout << color.pink << "EXIST\t" << color.white
            << ": EXIST key\t- check if entry exists\n";
  std::cout << color.pink << "DEL\t" << color.white
            << ": DEL key\t- delete entry\n";
  std::cout << color.pink << "UPDATE\t" << color.white
            << ": UPDATE key last_name first_name year city coins\n";
  std::cout << "\t'-' to skip column\t- change entry\n";
  std::cout << color.pink << "KEYS\t" << color.white
            << ": KEYS\t- print all keys in base\n";
  std::cout << color.pink << "RENAME\t" << color.white
            << ": RENAME old_key new_key\t- change the key of an entry\n";
  std::cout
      << color.pink << "TTL\t" << color.white
      << ": TTL key\t- show remaining time to live for a temporal entry\n";
  std::cout << color.pink << "FIND\t" << color.white
            << ": FIND last_name first_name year city coins\t- find all "
               "entries according to pattern\n";
  std::cout << color.pink << "SHOWALL\t" << color.white
            << ": SHOWALL\t- print all entries\n";
  std::cout << color.pink << "UPLOAD\t" << color.white
            << ": UPLOAD file_name\t- load a database from the file\n";
  std::cout << color.pink << "EXPORT\t" << color.white
            << ": EXPORT file_name\t- export the database to the file\n";
  std::cout << color.yellow << "help\t" << color.white
            << "- to see this help\n";
  std::cout << color.yellow << "clear\t" << color.white
            << "- clear the screen and see the header\n";
  std::cout << color.yellow << "q\t" << color.white << "- to quit\n";
  std::cout << std::endl;
}

void DialogDataBase::ClearScreen() {
  std::cout.flush();
  std::cin.clear();
  system("clear");
  draw_ = true;
}

void DialogDataBase::SlotSet() {
  std::string key{}, word{};
  StudentRecord record{};
  try {
    std::cin >> key >> record;
    int seconds{};
    bool exeption = false;
    if (std::cin.peek() != '\n') {
      std::cin >> word;
      if (std::cin.eof()) {
        exit(0);
      }
      std::transform(word.begin(), word.end(), word.begin(), ::toupper);
      if (word == "EX") {
        std::cin >> word;
        if (std::cin.eof()) exit(0);
        try {
          seconds = std::stoi(word);
        } catch (const std::exception &e) {
          exeption = true;
          std::cout << "> " << color.red << "Incorrect value time" << std::endl;
        }
      } else {
        exeption = true;
        std::cout << "> " << color.red << "only EX keyword can be here"
                  << std::endl;
      }
    }
    if (exeption == false) {
      auto answer = controller_->Set(key, record, seconds);
      std::cout << "> " << (answer.second ? color.green : color.red)
                << answer.first << color.end << std::endl;
    }
  } catch (const std::exception &e) {
    std::cout << "> " << color.red << "Incorrect input" << std::endl;
  }
}

void DialogDataBase::SlotGet() {
  std::string word{};
  word = ProtectedInput();
  std::cout << color.end;
  auto answer = controller_->Get(word);
  std::cout << "> " << (answer.second ? color.green : color.red) << answer.first
            << color.end << std::endl;
}

void DialogDataBase::SlotExist() {
  std::string word{};
  word = ProtectedInput();
  std::cout << color.end;
  auto answer = controller_->Exist(word);
  std::cout << "> " << (answer.second ? color.green : color.red) << answer.first
            << color.end << std::endl;
}

void DialogDataBase::SlotDel() {
  std::string word{};
  word = ProtectedInput();
  std::cout << color.end;
  auto answer = controller_->Del(word);
  std::cout << "> " << (answer.second ? color.green : color.red) << answer.first
            << color.end << std::endl;
}

void DialogDataBase::SlotUpdate() {
  std::string word{};
  StudentRecord record{};
  word = ProtectedInput();
  try {
    std::cin >> record;
    if (std::cin.eof()) {
      exit(0);
    }
    auto answer = controller_->Update(word, record);
    std::cout << "> " << (answer.second ? color.green : color.red)
              << answer.first << color.end << std::endl;
  } catch (const std::exception &e) {
    std::cout << "> " << color.red << "Incorrect input" << std::endl;
  }
}

void DialogDataBase::SlotKeys() {
  auto answer = controller_->Keys();
  std::cout << "> " << (answer.second ? color.green : color.red) << answer.first
            << color.end << std::endl;
}

void DialogDataBase::SlotRename() {
  std::string old_key{}, new_key{};
  old_key = ProtectedInput();
  new_key = ProtectedInput();
  std::cout << color.end;
  auto answer = controller_->Rename(old_key, new_key);
  std::cout << "> " << (answer.second ? color.green : color.red) << answer.first
            << color.end << std::endl;
}

void DialogDataBase::SlotTtl() {
  std::string word{};
  word = ProtectedInput();
  std::cout << color.end;
  auto answer = controller_->Ttl(word);
  std::cout << "> " << (answer.second ? color.green : color.red) << answer.first
            << color.end << std::endl;
}

void DialogDataBase::SlotFind() {
  StudentRecord record{};
  std::cout << color.blue;
  try {
    std::cin >> record;
    if (std::cin.eof()) {
      exit(0);
    }
    auto answer = controller_->Find(record);
    std::cout << "> " << (answer.second ? color.green : color.red)
              << answer.first << std::endl;
  } catch (const std::exception &e) {
    std::cout << "> " << color.red << "Incorrect input" << std::endl;
  }
}

void DialogDataBase::SlotShowAll() {
  auto all_records = controller_->ShowAll();
  std::cout
      << color.white
      << "№    |Last name     |First name    |Year |City          |Coins\n";
  std::cout
      << "-----+--------------+--------------+-----+--------------+------\n";
  std::cout << (all_records.second ? color.green : color.red);
  if (all_records.second == false) {
    std::cout << "Fail\n";
  } else if (all_records.first.empty()) {
    std::cout << "Database is empty\n";
  } else {
    for (size_t i{}; i < all_records.first.size(); i++) {
      std::string line{};
      line = std::to_string(i + 1);
      for (size_t j{line.size()}; j < 5; j++) line.append(" ");
      line.append("|");
      line.append(all_records.first[i].last_name_);
      for (size_t j{line.size()}; j < 20; j++) line.append(" ");
      line.append("|");
      line.append(all_records.first[i].first_name_);
      for (size_t j{line.size()}; j < 35; j++) line.append(" ");
      line.append("|");
      line.append(std::to_string(all_records.first[i].year_of_birth_));
      for (size_t j{line.size()}; j < 41; j++) line.append(" ");
      line.append("|");
      line.append(all_records.first[i].city_);
      for (size_t j{line.size()}; j < 56; j++) line.append(" ");
      line.append("|");
      line.append(std::to_string(all_records.first[i].coins_));
      std::cout << line << std::endl;
    }
  }
  std::cout << color.end;
}

void DialogDataBase::SlotUpload() {
  std::string word{};
  word = ProtectedInput();
  std::cout << color.end;
  if (word.size() < 4 || word.substr(word.size() - 4) != ".dat")
    word.append(".dat");
  auto answer = controller_->Upload(word);
  std::cout << "> " << (answer.second ? color.green : color.red) << answer.first
            << color.end << std::endl;
}

void DialogDataBase::SlotExport() {
  std::string word{};
  word = ProtectedInput();
  std::cout << color.end;
  if (word.size() < 4 || word.substr(word.size() - 4) != ".dat")
    word.append(".dat");
  auto answer = controller_->Export(word);
  std::cout << "> " << (answer.second ? color.green : color.red) << answer.first
            << color.end << std::endl;
}
