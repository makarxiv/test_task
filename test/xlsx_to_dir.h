#ifndef xlsx_to_dirH
#define xlsx_to_dirH
#include <string>

class XlsxToDir {
 public:
  void Unpacking(const std::string &file_name, const std::string &directory_name, const std::string &input_file_name);
  void UnzipFile(const std::string &file_name, const std::string &directory_name);
};

#endif