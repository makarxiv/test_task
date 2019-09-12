#ifndef cellH
#define cellH
#include <string>

class Cell {
 public:
  std::string value_;
  std::string name_;
  Cell() {
    name_ = "undefined";
    value_ = "undefined";
  }
  Cell(std::string name, std::string value) {
    name_ = name;
    value_ = value;
  }
};

#endif