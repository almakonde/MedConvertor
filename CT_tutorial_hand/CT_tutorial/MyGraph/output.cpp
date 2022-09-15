#include "output.h"

namespace output
{
	std::string out_string;
	
	void print(std::string s)
	{
		out_string += s;
	}
	void println(std::string s)
	{
		print(s);
		//print("<br>");
		print("\n");
	}

}