#ifndef LogH
#define LogH
#include <string>

class Log
{
private:
	std::string nfile;
	int log_mode;
public:
	void AddInLog(std::string message);
	Log(const std::string &name_file, bool clear_file, const int &log_mode_input);
	~Log();
};

#endif