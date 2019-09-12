#ifndef parse_parametersH
#define parse_parameters
#include <string>

class CommandLineParameters {
 public:
  std::string mode_;
  std::string input_file_name_; 
  std::string log_file_name_;
  int log_mode_;
  bool file_exist_;
  CommandLineParameters() {
	  mode_ = "dir";
	  input_file_name_ = "";
	  log_file_name_ = "";
	  log_mode_ = 1;
	  file_exist_ = false;
  }
  std::string ParseCommandLine(const int &argc, char *argv[]);
};

#endif