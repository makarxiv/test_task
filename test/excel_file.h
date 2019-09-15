#ifndef excel_fileH
#define excel_fileH
#include <vector>
#include <string>
#include "sheet.h"

class ExcelFile {
public:
  std::vector<std::string> strings_value_;
  ExcelFile() {};
  virtual ~ExcelFile() {};
  virtual void Parse() {};
};

#endif