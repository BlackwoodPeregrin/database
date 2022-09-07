#ifndef SRC_COLORS_HPP_
#define SRC_COLORS_HPP_

#include <iostream>

struct colors {
  const std::string red{"\e[1;91m"};
  const std::string green{"\e[1;92m"};
  const std::string yellow{"\e[1;93m"};
  const std::string blue{"\e[1;94m"};
  const std::string pink{"\e[1;95m"};
  const std::string azure{"\e[1;96m"};
  const std::string white{"\e[1;97m"};
  const std::string end{"\e[0m"};
};

#endif  // SRC_COLORS_H
