#include "xlsx_sheet.h"
#include "xlsx_tag.h"
#include <fstream>
#include <string>
#include <vector>
#include <sys/types.h>


void XlsxSheet::ReadSheet() {
  Cell res;
  std::string current_string;
  int pos = 0;
  setlocale(LC_ALL, "rus");
  std::ifstream file(sheet_file_name_);
  while (!file.eof()) {
    pos = 0;
    std::getline(file, current_string);
    while (true) {
      res = GetCell(current_string, pos);
      if (!(res.name_ == "undefined"))
        cells_.push_back(res);
      else
        break;
    }
  }
};

int XlsxSheet::ConvertIndexByValue(std::string &value,
                                 const std::vector<std::string> &strings_value_) {
    int num = std::stoi(value);
    if ((num==0)&&(!(value == "0"))) {
      value = "";
      return -1;
    }
    else {
      value = strings_value_[num];
      return 0;
    }
};

bool XlsxSheet::FindTag(const std::string &tag, const std::string &current_string,
                      int &currentpos, bool wrapping) {
  int pos1;
  std::string changed_tag;
  changed_tag = tag;
  if (wrapping) {
    if (tag.substr(0,1) != "<")
      changed_tag= "<" + changed_tag;
    if (tag.substr(tag.length() - 1,1) != ">")
      changed_tag= changed_tag + ">";
  }
  pos1 = current_string.find(changed_tag, currentpos);
  if (!(pos1 == std::string::npos)) {
    currentpos = pos1;
    return true;
  }
  else
  {
    currentpos = std::string::npos;
    return false;
  }
};

Cell XlsxSheet::GetCell(const std::string &current_string, int &startpos) {
  int pos1 = startpos;
  std::string val = "";
  Cell out_cell;
  if (FindTag(XlsxTag::kTagCell, current_string, pos1, false)) {
    int pos2 = pos1;
    if (FindTag(">", current_string, pos2, false)) {
      std::string fulltag = current_string.substr(pos1, pos2 - pos1 + 1);
      int posv1 = pos2;
      int posv2 = pos2;
	  if ((FindTag(XlsxTag::kTagValue, current_string, posv1, true))&&
		  (FindTag("/" + XlsxTag::kTagValue, current_string, posv2, true))) {
            int trigger = fulltag.find(XlsxTag::kTagCellString);
        if (trigger == std::string::npos) {
          out_cell.value_ = current_string.substr(posv1 + 3, posv2 - posv1 - 3);
          out_cell.name_ = current_string.substr(pos1 + 6, posv1 - pos1 - 8);
        }
        else {
          val = current_string.substr(posv1 + 3, posv2 - posv1 - 3);
          ConvertIndexByValue(val, *strings_value_);
          out_cell.value_ = val;
          out_cell.name_ = current_string.substr(pos1 + 6, posv1 - pos1 - 14);
        }
        startpos = posv2 + 4;
        return out_cell;
      }
      else {
        return out_cell;
      }

    }
    else {
      return out_cell;
    }
  }
  else {
    return out_cell;
  }
};
  