#pragma once

#include <vector>
#include <string>

class StringHelper
{
public:
	static std::vector<std::string> Tokenize(std::string str, char delim);
};

