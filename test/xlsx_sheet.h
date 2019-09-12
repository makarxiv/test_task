#ifndef xlsx_sheetH
#define xlsx_sheetH
#include "cell.h"
#include "sheet.h"
#include <vector>
#include <string>

class XlsxSheet : public Sheet {
 public:
  std::string sheet_file_name_;
  std::vector<std::string> *strings_value_;
  void ReadSheet();
 protected:
  Cell GetCell(const std::string &current_string, int &startpos);
  bool FindTag(const std::string &tag, const std::string &current_string,
             int &currentpos, bool wrapping);
  int ConvertIndexByValue(std::string &value,
                        const std::vector<std::string> &strings_value_);
};

#endif