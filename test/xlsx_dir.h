#ifndef xlsx_dirH //я проверил, это нужная фича, защищает от дублирующих включений этого файла (и, получается, от переопределния класса, например)
#define xlsx_dirH
#include <vector>
#include <string>
#include "xlsx_sheet.h"
#include "excel_file.h"

class XlsxDir : public ExcelFile {
 public:
  std::vector<XlsxSheet> sheets_;
  std::string directory_name_;
  XlsxDir(std::string &input_name);
  void Parse();
protected:
  void FindTag(const std::string &tag, const std::string &current_string,
             int &currentpos);
  int FillTagValue(const std::string &tag, const std::string &scurrent_string, 
                 int &startpos, std::string &value);
  void FillStringsValue();
  void FindSheets();
  std::string GetSheetsName(const int &number_sheet);
  std::string strings_file_name_, directory_sheets_, sheet_file_name_;
};

#endif