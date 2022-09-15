#ifndef OUTPUT_INC
#define OUTPUT_INC

#include <stdlib.h>
#include <string>
#include "str.h"

namespace output
{
	extern std::string out_string;

	void print(std::string s);
	void println(std::string s);
}

#endif