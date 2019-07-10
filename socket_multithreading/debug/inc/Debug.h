#ifndef DEBUG_H_
#define DEBUG_H_

#include <string>

using namespace std;

class Debug
{
public:
	enum Colors
	{
		CL_RED = 1,
		CL_GREEN,
		CL_YELLOW,
		CL_BLUE,
		CL_MAGENTA,
		CL_CYAN,
		CL_WHITE,
		CL_NORMAL
	};

	static string generateMsg(const char *format, ...);
	static int print(Colors color, const char *format, ...);

private:
	static const char *getColor(Colors color = CL_NORMAL);
	static string translate(const char *format, va_list va);
};

#endif
