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
#include "xlsx_to_dir.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <cstdint>
#include <windows.h>
 
bool isDirectoryExists(const char *filename)
{
  DWORD dwFileAttributes = GetFileAttributes(filename);
  if (dwFileAttributes == 0xFFFFFFFF)
    return false;
  return dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
}

bool checkFileExist(std::string &input_file_name, const std::string &mode) {
  bool file_exist(false);
  if (mode == "xlsx") {
    file_exist = std::ifstream(input_file_name) != NULL;
    if (!file_exist)
      std::cout << "File not found." << std::endl;
    while (!file_exist) {
      std::cout << "Enter file name: ";
      std::cin >> input_file_name;
      file_exist = std::ifstream(input_file_name) != NULL;
      if (!file_exist)
        std::cout << "File not found." << std::endl;
    }
  return file_exist;
  }
  if (mode == "dir") {
	file_exist = isDirectoryExists(input_file_name.c_str());
    if (!file_exist)
      std::cout << "File not found." << std::endl;
    while (!file_exist) {
      std::cout << "Enter file name: ";
      std::cin >> input_file_name;
	  file_exist = isDirectoryExists(input_file_name.c_str());
      if (!file_exist)
        std::cout << "File not found." << std::endl;
    }
  return file_exist;
  }
  return file_exist;
}

int _tmain(int argc, char *argv[])
{
  CommandLineParameters param;
  std::string error_command;
  error_command = param.ParseCommandLine(argc, argv);
  if (error_command != "")
    std::cout << error_command << std::endl;
  if ((param.mode_ != "dir")&&(param.mode_ != "xlsx")) {
    std::cout << "Selected metod not supported in this version." << std::endl;
    std::cin.get();
    return 1;
  }
  std::string input_file_name = param.input_file_name_;
  if (!checkFileExist(input_file_name, param.mode_)) {
    std::cout << "Incorrect input data." << std::endl;
    std::cin.get();
    return 1;
  }
  std::string output_directory = input_file_name;
  if (param.mode_ == "xlsx")
    output_directory = input_file_name.substr(0, input_file_name.find(".xlsx"));
  std::string output_file_name_zip = output_directory + ".zip";
  std::string output_file_name = output_directory + ".txt";
  std::string log_file_name;
  if (param.log_file_name_ == "")
    log_file_name = output_directory + ".log";
  else
    log_file_name = param.log_file_name_;
  Log logfile(log_file_name, true, param.log_mode_);
  logfile.AddInLog("start logging;", 1);
  if (param.mode_ == "xlsx") {
    try {
      XlsxToDir extracter;
      extracter.Unpacking(output_file_name_zip, output_directory, input_file_name);
    }
    catch (std::string msg) {
	  logfile.AddInLog(msg, 0);
      std::cout << msg << std::endl;	
	  std::cin.get();
	  return 1;
    }
  }
  XlsxDir dir(output_directory);
  logfile.AddInLog("create instance of XlsxDir;", 1);
  try {
    dir.Parse();
  }
  catch (std::string msg) {
	logfile.AddInLog(msg, 0);
    std::cout << msg << std::endl;	
	std::cin.get();
	return 1;
  }
  std::ofstream output_file(output_file_name);
  if (!(output_file.is_open())) {
    logfile.AddInLog("error opening file of result;", 0);
    return 1;
  }
  else
  {
    logfile.AddInLog("successful opening file of result;", 1);
  }
  for(auto its = dir.sheets_.begin(); its != dir.sheets_.end(); its++) {
    output_file << "Sheet " << its->sheet_name_ << std::endl;
    for(auto itc = its->cells_.begin(); itc != its->cells_.end(); itc++)
      output_file << "Cell " << itc->name_ << "; value:" << itc->value_ << std::endl;
  }
  output_file.close();

  return 0;
};

