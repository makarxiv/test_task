#include "xlsx_dir.h"
#include "xlsx_sheet.h"
#include "dirent.h"
#include "xlsx_tag.h"
#include <fstream>
#include <string>
#include <vector>
#include <sys/types.h>

XlsxDir::XlsxDir(std::string &input_name):ExcelFile() {
  directory_name_ = input_name;
  if (!(input_name[input_name.length() - 1] == '\\'))
    input_name = input_name + "\\";
  sheet_file_name_ = input_name + XlsxTag::kNameSheetPath;
  directory_sheets_ = input_name + XlsxTag::kSheetsDirectory;
  strings_file_name_ = input_name + XlsxTag::kPathToStrings;
};

int XlsxDir::Parse() {
  int res = 0;
  FindSheets();
  FillStringsValue();
  for (auto it = sheets_.begin(); it != sheets_.end(); it++)
    it->ReadSheet();
  return res;
};

std::string XlsxDir::GetSheetsName(const int &number_sheet) {
  int number_string = 0;
  int currentpos = 0;
  int res = 0;
  std::string current_value = "";
  std::string current_string;
  std::ifstream file(sheet_file_name_);
  while (!file.eof()) {
    std::getline(file, current_string);
	FindTag(XlsxTag::kTagTitles, current_string, currentpos);
    while (number_string != (number_sheet - 1)) {
		FindTag(XlsxTag::kTagSheetName, current_string, currentpos);
      if (currentpos == std::string::npos)
        break;
      number_string++;
    }
    if (currentpos == std::string::npos) {
      currentpos = 0;
    }
    else {
		res = FillTagValue(XlsxTag::kTagSheetName, current_string, currentpos, current_value); 
      return current_value;
    }
  }

};

void XlsxDir::FindTag(const std::string &tag, const std::string &current_string,
                    int &currentpos) {
  int pos1;
  std::string stag= "<" + std::string(tag) + ">";
  pos1 = current_string.find(stag, currentpos);
  if (!(pos1 == std::string::npos))
    currentpos = pos1 + stag.length();
  else
    currentpos = std::string::npos;
};

int XlsxDir::FillTagValue(const std::string &tag, const std::string &current_string,
                        int &startpos, std::string &value) {
  FindTag(tag, current_string, startpos);
  if (!(startpos == std::string::npos)) {
    int pos1 = startpos;
    std::string close_tag = "/" + tag;
    FindTag(close_tag, current_string, startpos);
    if (!(startpos == std::string::npos)) {
      value = current_string.substr(pos1, startpos - pos1 - close_tag.length() - 2);
      return 0;
    }
    else {
      return -2;
    }
  }
  else {
    return -1;
  }
};

void XlsxDir::FillStringsValue() {
  int res;
  std::string current_string;
  std::string inside_tag;
  std::string value;
  std::ifstream file(strings_file_name_.c_str());
  while (!file.eof()) {
    std::getline(file, current_string);
    int pos = 0;
    while (!(pos == std::string::npos)) {
		res = FillTagValue(XlsxTag::kTagStringValueExternal, current_string, pos, value);
      if (res == 0) {
        inside_tag = value; // value = <t>%value%</t>
        int inside_pos = 0;
		res = FillTagValue(XlsxTag::kTagStringValueInternal, inside_tag, inside_pos, value);
        if (res==0)
          strings_value_.push_back(value);
        //else
          //break; //inside correct file we don't find this place never
      }
      else {
        break;
      }
    }
  }
};

int XlsxDir::FindSheets() {
  DIR *dir = opendir(directory_sheets_.c_str());
  std::string fname;
    if(dir) {
        struct dirent *ent;
        while((ent = readdir(dir)) != NULL) {
      fname = std::string(ent -> d_name);
      if (!(fname.find("sheet") == std::string::npos)) {
        int sheet_num = 0;
        std::string sheet_str = fname.substr(5, fname.length() - 9);
        sheet_num = std::stoi(sheet_str);
        sheet_str = GetSheetsName(sheet_num);
        if (!(sheet_str == "")) {
          XlsxSheet current_sheet;
          current_sheet.sheet_file_name_ = directory_sheets_ + fname;
          current_sheet.sheet_name_ = sheet_str;
          current_sheet.strings_value_ = &strings_value_;
          sheets_.push_back(current_sheet);
        }
      }
        }
    delete dir;
    delete ent;
    }
  if (sheets_.empty())
    return 1;
  else
    return 0;
};
  