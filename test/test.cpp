// test_task.cpp: определяет точку входа для консольного приложения.
//

//#include "unzip.h"
#include "stdafx.h"
#include "cell.h"
#include "xlsx_sheet.h"
#include "xlsx_dir.h"
#include "excel_file.h"
#include "sheet.h"
#include "log.h"
#include "parse_parameters.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <cstdint>

int _tmain(int argc, char *argv[])
{
  int res;
  bool file_exist(false);
  CommandLineParameters param;
  std::string error_command;
  error_command = param.ParseCommandLine(argc, argv);
  if (error_command != "")
    std::cout << error_command << std::endl;
  if (param.mode_ != "dir") {
    std::cout << "Selected metod not supported in this version." << std::endl;
    std::cin.get();
    return 0;
  }
  std::string input_file_name = param.input_file_name_;
  file_exist = param.file_exist_;
  while (!file_exist) {
    std::cout << "Enter file name: ";
    std::cin >> input_file_name;
    file_exist = std::ifstream(input_file_name) != NULL;
    if (!file_exist)
      std::cout << "File not found." << std::endl;
  }
  std::string output_directory = input_file_name.substr(0, input_file_name.find(".xlsx"));
  //std::string output_file_name_zip = output_directory + ".zip";
  std::string output_file_name = output_directory + ".txt";
  std::string log_file_name;
  if (param.log_file_name_ == "")
    log_file_name = output_directory + ".log";
  else
    log_file_name = param.log_file_name_;
//  Zip archive;
//  archive.Extract(input_file_name,output_directory);
  Log logfile(log_file_name, true, param.log_mode_);
  logfile.AddInLog("start logging;");
  XlsxDir dir(output_directory);
  logfile.AddInLog("create instance of XlsxDir;");
  res = dir.Parse();
  if (!(res == 0)) {
    logfile.AddInLog("error reading file of name sheets;");
    return res;
  }
  else
  {
    logfile.AddInLog("successful reading file of name sheets;");
  }
  std::ofstream output_file(output_file_name);
  if (!(output_file.is_open())) {
    logfile.AddInLog("error opening file of result;");
    return 1;
  }
  else
  {
    logfile.AddInLog("successful opening file of result;");
  }
  for(auto its = dir.sheets_.begin(); its != dir.sheets_.end(); its++) {
    output_file << "Sheet " << its->sheet_name_ << std::endl;
    for(auto itc = its->cells_.begin(); itc != its->cells_.end(); itc++)
      output_file << "Cell " << itc->name_ << "; value:" << itc->value_ << std::endl;
  }
  output_file.close();

  return 0;
};

