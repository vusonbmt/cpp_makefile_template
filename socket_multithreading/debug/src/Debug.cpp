#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "Debug.h"

#define KRED  "\x1B[31m" // Red
#define KGRN  "\x1B[32m" // Green
#define KYEL  "\x1B[33m" // Yellow
#define KBLU  "\x1B[34m" // Blue
#define KMAG  "\x1B[35m" // Magenta
#define KCYN  "\x1B[36m" // Cyan
#define KWHT  "\x1B[37m" // White
#define KNRM  "\x1B[0m"  // Normal

#define MSG_MAX_LEN 1024

// Return color code.
const char *Debug::getColor(Colors color)
{
	const char *colorCode = nullptr;
	switch(color)
	{
		case CL_RED:
			colorCode = KRED;
			break;
		case CL_GREEN:
			colorCode = KGRN;
			break;
		case CL_YELLOW:
			colorCode = KYEL;
			break;
		case CL_BLUE:
			colorCode = KBLU;
			break;
		case CL_MAGENTA:
			colorCode = KMAG;
			break;
		case CL_CYAN:
			colorCode = KCYN;
			break;
		case CL_WHITE:
			colorCode = KWHT;
			break;
		case CL_NORMAL:
			colorCode = KNRM;
			break;
		default:
			colorCode = KNRM;
			break;
	}
	return colorCode;
}

// Convert va list in string.
string Debug::translate(const char *format, va_list va)
{
	char msg[MSG_MAX_LEN];
	vsnprintf(msg, sizeof(msg), format, va);
	return string(msg);
}

// Convert all arguments in string.
string Debug::generateMsg(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	return translate(format, ap);
}

// Print debug message.
int Debug::print(Colors color, const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	return printf("%s%s%s", getColor(color), translate(format, ap).c_str(), getColor());
}
