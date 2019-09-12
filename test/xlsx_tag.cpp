#include "xlsx_tag.h"
#include <string>

const std::string XlsxTag::kNameSheetPath = "docProps\\app.xml";
const std::string XlsxTag::kSheetsDirectory = "xl\\worksheets\\";
const std::string XlsxTag::kPathToStrings = "xl\\sharedStrings.xml";
const std::string XlsxTag::kTagTitles = "TitlesOfParts";
const std::string XlsxTag::kTagSheetName = "vt:lpstr";
const std::string XlsxTag::kTagStringValueExternal = "si";
const std::string XlsxTag::kTagStringValueInternal = "t";
const std::string XlsxTag::kTagCell = "<c r=";
const std::string XlsxTag::kTagCellString = " t=\"s\"";
const std::string XlsxTag::kTagValue = "v";