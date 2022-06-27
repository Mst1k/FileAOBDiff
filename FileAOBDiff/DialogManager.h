#pragma once

#include <string>

class DialogManager
{
public:
	static bool AskPath(const std::string targetFileName, std::string& outPath);
};

