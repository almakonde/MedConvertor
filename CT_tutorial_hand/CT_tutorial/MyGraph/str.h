#ifndef STR_H
#define STR_H

#include "AllDef.h"
#include <memory.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "vec3.h"

#include <sstream>


namespace str
{
	std::vector<std::string> split(const std::string& source,std::string delim=" ");
	float ToFloat(std::string s);
	int ToInt(std::string s);
	
	std::string ToString(int val);
	std::string ToString(float val);
	std::string ToString(vec3 val);


	typedef std::vector<std::pair<std::string,std::string>> StringPairs;
	std::string replace(std::string target, std::string that, std::string with);
	std::string ReplaceInString(std::string s,StringPairs& repl);
	void ReplaceInFile(std::string fn,std::string nfn,StringPairs& repl);
	void AddPair(StringPairs& arr, std::string a, std::string b);

};

#endif