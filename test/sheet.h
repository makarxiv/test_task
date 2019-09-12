#ifndef sheetH
#define sheetH
#include "cell.h"
#include <vector>
#include <string>

class Sheet {
 public:
  std::string sheet_name_;
  std::vector<Cell> cells_;
  Sheet() {};
  virtual void GetCells() {};
  virtual ~Sheet() {};
};

#endif