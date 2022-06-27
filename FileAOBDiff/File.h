#pragma once

#include <string>

struct Buffer;

struct File {
	std::string filePathStr;
	Buffer* pBuff;

	File();
	~File();

	bool ValidOffset(uint64_t offset) const;
};
