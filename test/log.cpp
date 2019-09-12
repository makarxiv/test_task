#include "log.h"
#include <fstream>
#include <ctime>

Log::Log(const std::string &name_file, bool clear_file, const int &log_mode_input) {
  char symbol = std::ios::app;
  if (clear_file)
    symbol = std::ios::out;
  nfile = name_file;
  log_mode = log_mode_input;
  if (log_mode != 0) {
    std::ofstream file(name_file.c_str(), symbol);
    file.close();
  }
};

Log::~Log() {
  AddInLog("finish logging.");
};

void Log::AddInLog(std::string message)
{
  if (log_mode !=0) {
    std::ofstream file(nfile.c_str(), std::ios::app);
    time_t seconds = time(NULL);
    tm *timeinfo = std::localtime(&seconds);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
    file << buffer << ":" << message << std::endl;
    file.close();
  }
};