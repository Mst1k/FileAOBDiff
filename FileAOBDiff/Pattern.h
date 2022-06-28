#pragma once

#include <vector>
#include <string>
#include "PatternByte.h"

struct Pattern
{

private:
	std::vector<PatternByte> aob;

public:
	Pattern();

	std::string cachedStr;

	void CacheStr();
	void InvalidateCache();
	std::string toString();
	void AddByte(unsigned char byte, bool bIsWildCard = false);
	void AddWildCard();
	std::vector<unsigned char> getBytes() const;
};

