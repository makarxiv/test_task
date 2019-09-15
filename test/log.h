#ifndef LogH
#define LogH
#include <string>

class Log
{
private:
	std::string nfile;
	int log_mode;
public:
	void AddInLog(const std::string &message, const int &log_lvl);
	Log(const std::string &name_file, bool clear_file, const int &log_mode_input);
	~Log();
};

#endif