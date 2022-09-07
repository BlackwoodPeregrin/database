#include "dialog_research.hpp"

#include <chrono>
#include <random>

void DialogResearch::Show() {
  while (m_exit == false) {
    if (m_draw == true) {
      PrintMainMenu_();
      m_draw = false;
    }
    ScanfInput_();
  }
}

void DialogResearch::PrintMainMenu_() {
  system("clear");
  std::cout << color.blue << " ======= Research Transactions ======= \n";
  std::cout << color.white << " Number of Items:\t" << color.yellow
            << m_sum_items << "\n";
  std::cout << color.white << " Number of Actions:\t" << color.yellow
            << m_sum_actions << "\n";
  std::cout << color.blue << "=======================================\n";
  std::cout << color.azure;
  std::cout << "1 - Sets The Number of Items In Containers\n";
  std::cout << "2 - Sets The Number of Actions\n";
  std::cout << "3 - Start Research\n";
  std::cout << "4 - Come Back" << color.end << std::endl;
}

void DialogResearch::ScanfInput_() {
  int choose = ProtectedInput_();
  PrintMainMenu_();
  if (choose == 1) {
    InstallSumItems_();
  } else if (choose == 2) {
    InstallSumActions_();
  } else if (choose == 3) {
    StartTest_();
  } else if (choose == 4) {
    m_exit = true;
  } else {
    ColorPrint_("Error, incorrect choose. Try again.", color.red, color.end);
  }
  if (m_exit != true) {
    PauseFunc_();
  }
}

void DialogResearch::StartTest_() {
  if (m_sum_items == 0 || m_sum_actions == 0) {
    ColorPrint_(
        "Input parametrs: 'Number of Items' and 'Number of Actions', "
        "for start test.",
        color.red, color.end);
  } else {
    ColorPrint_("Running Tests...\n", color.green, color.end);
    // создаем оба контейнера
    m_conroller1 = new Controller(Controller::BaseRealisation::kHashTable);
    m_conroller2 = new Controller(Controller::BaseRealisation::kBinaryTree);

    // генериуем рандомные значения для контейнера
    std::vector<std::pair<std::string, StudentRecord>> key_value;
    for (size_t i = 0; i < m_sum_items; ++i) {
      key_value.push_back(std::make_pair(GenerateKey_(), GenerateStructStudent_()));
    }

    // Заполянем контейры этими значениями
    for (size_t i = 0; i < key_value.size(); ++i) {
      m_conroller1->Set(key_value[i].first, key_value[i].second);
      m_conroller2->Set(key_value[i].first, key_value[i].second);
    }

    // Получение произвольного элемента
    std::pair<double, double> test = TestGetElement_(key_value);
    //
    ColorPrint_("Getting an arbitrary element Test:", color.green, color.end);
    std::cout << color.white << "Hash Table:\t" << color.yellow << test.first
              << " ms.\n"
              << std::endl;
    std::cout << color.white << "Binary Tree:\t" << color.yellow << test.second
              << " ms.\n"
              << std::endl;

    // Добавление элемента
    test = TestAddElement_();
    //
    ColorPrint_("Adding an element Test:", color.green, color.end);
    std::cout << color.white << "Hash Table:\t" << color.yellow << test.first
              << " ms.\n"
              << std::endl;
    std::cout << color.white << "Binary Tree:\t" << color.yellow << test.second
              << " ms.\n"
              << std::endl;

    // Получения списка всех элементов в словаре
    test = TestGetAllElements_();
    //
    ColorPrint_("Getting a list of all elements in a dictionary Test:\t",
                color.green, color.end);
    std::cout << color.white << "Hash Table:\t" << color.yellow << test.first
              << " ms.\n"
              << std::endl;
    std::cout << color.white << "Binary Tree:\t" << color.yellow << test.second
              << " ms.\n"
              << std::endl;
    // Поиск ключа элемента по значению
    test = TestFindKey_(key_value);
    //
    ColorPrint_("Finding an element key by value Test:", color.green,
                color.end);
    std::cout << color.white << "Hash Table:\t" << color.yellow << test.first
              << " ms.\n"
              << std::endl;
    std::cout << color.white << "Binary Tree:\t" << color.yellow << test.second
              << " ms.\n"
              << std::endl;
    // Удаление элемента
    test = TestDeleteElement_(key_value);
    //
    ColorPrint_("Removing an element Test:", color.green, color.end);
    std::cout << color.white << "Hash Table:\t" << color.yellow << test.first
              << " ms.\n"
              << std::endl;
    std::cout << color.white << "Binary Tree:\t" << color.yellow << test.second
              << " ms.\n"
              << std::endl;

    // удаляем оба контейнера
    delete m_conroller1;
    delete m_conroller2;
  }
}

int DialogResearch::ProtectedInput_() {
  std::string input{};
  std::cout << color.yellow;
  std::cin >> input;
  std::cout << color.end;
  if (std::cin.eof()) {
    exit(0);
  }
  try {
    int choose{};
    choose = std::stoi(input);
    return choose;
  } catch (const std::exception& e) {
    return -1;
  }
}

void DialogResearch::InstallSumItems_() {
  ColorPrint_("Input Number of Items:", color.white, color.end);
  int tmp = ProtectedInput_();
  if (tmp == -1) {
    ColorPrint_("Error, incorrect choose. Try again.", color.red, color.end);
  } else if (tmp < 1) {
    ColorPrint_("Error, Number of Actions must be '>1'.", color.red, color.end);
  } else {
    m_sum_items = tmp;
    ColorPrint_("Number of Items Install SUCSESS.", color.green, color.end);
  }
}

void DialogResearch::InstallSumActions_() {
  ColorPrint_("Input Number of Actions:", color.white, color.end);
  int tmp = ProtectedInput_();
  if (tmp == -1) {
    ColorPrint_("Error, incorrect choose. Try again.", color.red, color.end);
  } else if (tmp < 1) {
    ColorPrint_("Error, Number of Actions must be '>1'.", color.red, color.end);
  } else {
    m_sum_actions = tmp;
    ColorPrint_("Number of Items Install SUCSESS.", color.green, color.end);
  }
}

void DialogResearch::PauseFunc_() {
  std::string key{};
  std::cout << color.blue;
  std::cout << "Enter any key to continue ... ";
  std::cin >> key;
  std::cout << color.end << std::endl;
  if (std::cin.eof()) {
    exit(0);
  }
  m_draw = true;
}

void DialogResearch::ColorPrint_(const std::string& message,
                                 const std::string& color_start,
                                 const std::string& color_end) {
  std::cout << color_start;
  std::cout << message;
  std::cout << color_end << std::endl;
}

/* ============================= Tests ================================= */

std::pair<double, double> DialogResearch::TestGetElement_(
    const std::vector<std::pair<std::string, StudentRecord>>& key_value) {
  double all_wasted_time1{};
  double all_wasted_time2{};

  for (size_t i = 0; i < m_sum_actions; ++i) {
    size_t index_element = GetRandom(0, key_value.size() - 1);
    /*--- Hash Table ---*/
    auto time_start = std::chrono::high_resolution_clock::now();
    m_conroller1->Get(key_value[index_element].first);
    auto time_end = std::chrono::high_resolution_clock::now();
    all_wasted_time1 += std::chrono::duration_cast<std::chrono::microseconds>(
                            (time_end - time_start))
                            .count();

    /*--- Binary Tree ---*/
    time_start = std::chrono::high_resolution_clock::now();
    m_conroller2->Get(key_value[index_element].first);
    time_end = std::chrono::high_resolution_clock::now();
    all_wasted_time2 += std::chrono::duration_cast<std::chrono::microseconds>(
                            (time_end - time_start))
                            .count();
  }

  // сохраняем результаты
  std::pair<double, double> result{};
  result.first = (all_wasted_time1 / (double)m_sum_actions) * kMicroToMs;
  result.second = (all_wasted_time2 / (double)m_sum_actions) * kMicroToMs;
  return result;
}

std::pair<double, double> DialogResearch::TestAddElement_() {
  double all_wasted_time1{};
  double all_wasted_time2{};

  for (size_t i = 0; i < m_sum_actions; ++i) {
    std::string key(std::move(GenerateKey_()));
    StudentRecord value(std::move(GenerateStructStudent_()));

    /*--- Hash Table ---*/
    auto time_start = std::chrono::high_resolution_clock::now();
    m_conroller1->Set(key, value);
    auto time_end = std::chrono::high_resolution_clock::now();
    all_wasted_time1 += std::chrono::duration_cast<std::chrono::microseconds>(
                            (time_end - time_start))
                            .count();

    /*--- Binary Tree ---*/
    time_start = std::chrono::high_resolution_clock::now();
    m_conroller2->Set(key, value);
    time_end = std::chrono::high_resolution_clock::now();
    all_wasted_time2 += std::chrono::duration_cast<std::chrono::microseconds>(
                            (time_end - time_start))
                            .count();
  }

  // сохраняем результаты
  std::pair<double, double> result{};
  result.first = (all_wasted_time1 / (double)m_sum_actions) * kMicroToMs;
  result.second = (all_wasted_time2 / (double)m_sum_actions) * kMicroToMs;
  return result;
}

std::pair<double, double> DialogResearch::TestGetAllElements_() {
  double all_wasted_time1{};
  double all_wasted_time2{};

  for (size_t i = 0; i < m_sum_actions; ++i) {
    /*--- Hash Table ---*/
    auto time_start = std::chrono::high_resolution_clock::now();
    m_conroller1->ShowAll();
    auto time_end = std::chrono::high_resolution_clock::now();
    all_wasted_time1 += std::chrono::duration_cast<std::chrono::microseconds>(
                            (time_end - time_start))
                            .count();

    /*--- Binary Tree ---*/
    time_start = std::chrono::high_resolution_clock::now();
    m_conroller2->ShowAll();
    time_end = std::chrono::high_resolution_clock::now();
    all_wasted_time2 += std::chrono::duration_cast<std::chrono::microseconds>(
                            (time_end - time_start))
                            .count();
  }

  // сохраняем результаты
  std::pair<double, double> result{};
  result.first = (all_wasted_time1 / (double)m_sum_actions) * kMicroToMs;
  result.second = (all_wasted_time2 / (double)m_sum_actions) * kMicroToMs;
  return result;
}

std::pair<double, double> DialogResearch::TestFindKey_(
    const std::vector<std::pair<std::string, StudentRecord>>& key_value) {
  double all_wasted_time1{};
  double all_wasted_time2{};

  for (size_t i = 0; i < m_sum_actions; ++i) {
    size_t index_element = GetRandom(0, key_value.size() - 1);
    /*--- Hash Table ---*/
    auto time_start = std::chrono::high_resolution_clock::now();
    m_conroller1->Find(key_value[index_element].second);
    auto time_end = std::chrono::high_resolution_clock::now();
    all_wasted_time1 += std::chrono::duration_cast<std::chrono::microseconds>(
                            (time_end - time_start))
                            .count();

    /*--- Binary Tree ---*/
    time_start = std::chrono::high_resolution_clock::now();
    m_conroller2->Find(key_value[index_element].second);
    time_end = std::chrono::high_resolution_clock::now();
    all_wasted_time2 += std::chrono::duration_cast<std::chrono::microseconds>(
                            (time_end - time_start))
                            .count();
  }

  // сохраняем результаты
  std::pair<double, double> result{};
  result.first = (all_wasted_time1 / (double)m_sum_actions) * kMicroToMs;
  result.second = (all_wasted_time2 / (double)m_sum_actions) * kMicroToMs;
  return result;
}

std::pair<double, double> DialogResearch::TestDeleteElement_(
    const std::vector<std::pair<std::string, StudentRecord>>& key_value) {
  double all_wasted_time1{};
  double all_wasted_time2{};

  for (size_t i = 0; i < m_sum_actions; ++i) {
    size_t index_element = GetRandom(0, key_value.size() - 1);
    /*--- Hash Table ---*/
    auto time_start = std::chrono::high_resolution_clock::now();
    m_conroller1->Del(key_value[index_element].first);
    auto time_end = std::chrono::high_resolution_clock::now();
    all_wasted_time1 += std::chrono::duration_cast<std::chrono::microseconds>(
                            (time_end - time_start))
                            .count();
    /*--- Binary Tree ---*/
    time_start = std::chrono::high_resolution_clock::now();
    m_conroller2->Del(key_value[index_element].first);
    time_end = std::chrono::high_resolution_clock::now();
    all_wasted_time2 += std::chrono::duration_cast<std::chrono::microseconds>(
                            (time_end - time_start))
                            .count();
  }

  // сохраняем результаты
  std::pair<double, double> result{};
  result.first = (all_wasted_time1 / (double)m_sum_actions) * kMicroToMs;
  result.second = (all_wasted_time2 / (double)m_sum_actions) * kMicroToMs;
  return result;
}

/* ========================= Random Generator ======================== */

std::string DialogResearch::GenerateKey_() {
  std::string key{};
  // генерируем длину
  int tmp = GetRandom(1, 20);
  // генерируем символы
  for (int j = 0; j < tmp; ++j) {
    key.push_back(GetRandom(97, 122));
  }
  return key;
}

StudentRecord DialogResearch::GenerateStructStudent_() {
  StudentRecord value{};
  // генерируем фамилию
  int tmp = GetRandom(1, 20);
  for (int j = 0; j < tmp; ++j) {
    value.last_name_.push_back(GetRandom(97, 122));
  }

  // генерируем имя
  tmp = GetRandom(1, 20);
  for (int j = 0; j < tmp; ++j) {
    value.first_name_.push_back(GetRandom(97, 122));
  }

  // генерируем дату рождения
  value.year_of_birth_ = GetRandom(1950, 2022);

  // генерируем город проживания
  int tmp_name_town = GetRandom(1, 20);
  for (int j = 0; j < tmp_name_town; ++j) {
    value.city_.push_back(GetRandom(97, 122));
  }

  // генерируем количетсво коинов
  value.coins_ = GetRandom(0, 10000);
  return value;
}

int DialogResearch::GetRandom(int left_limit, int right_limit) {
  // install random
  std::random_device dev;
  std::mt19937 gen(dev());
  std::uniform_real_distribution<double> result(left_limit, right_limit);
  return result(gen);
}
