#include "parse_parameters.h"
#include <fstream>
#include <string>

std::string CommandLineParameters::ParseCommandLine(const int &argc, char *argv[]) {
  std::string error = "";
  if (argc > 0) {
    int i = 1;
    while (i < argc) {
      int pos;
      std::string parameter = std::string(argv[i]);
      if ((parameter == "mode")&&((i + 1) < argc)) {
        mode_ = std::string(argv[i+1]);
        i = i + 2;
        continue;
      }
      if ((parameter == "path")&&((i + 1) < argc)) {
        input_file_name_ = std::string(argv[i+1]);
        file_exist_ = std::ifstream(input_file_name_) != NULL;
        if (!file_exist_)
			error = error + "Incorrect parameter file name (parameter " + input_file_name_ + ").";
        i = i + 2;
        continue;
      }
      if (parameter == "v") {
        log_mode_ = 2;
        i = i + 1;
        continue;
      }  
      if (parameter == "n") {
        log_mode_ = 0;
        i = i + 1;
        continue;
      }  
      if ((parameter == "log")&&((i + 1) < argc)) {
        log_file_name_ = std::string(argv[i+1]);
        i = i + 2;
		continue;
      }
	  error = error + "Unidentified parameter " + parameter + ".";
      i = i + 1;

    }
  }
  if (error != "")
	  error = error + "Acceptable values: n(disable log), v(extended log), log %log_file_name%, path %file_name_for_parsing%, mode %mode% (dir, xls or xlsx).";
  return error;
};