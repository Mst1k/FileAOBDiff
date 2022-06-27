#include "DialogManager.h"
#include <Windows.h>
#include <vector>

bool DialogManager::AskPath(const std::string targetFileNameStr, std::string& outPath)
{
	OPENFILENAMEA ofn;
	char outPathCStr[MAX_PATH]{};
	const std::string pAllFilterStr = "*.*";

	std::vector<char> fullFilter;

	for (char c : targetFileNameStr) fullFilter.push_back(c);
	fullFilter.push_back('\0');
	fullFilter.push_back('\0');

	for (char c : pAllFilterStr) fullFilter.push_back(c); 
	fullFilter.push_back('\0');
	fullFilter.push_back('\0');

	// open a file name
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = outPathCStr;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = (LPSTR)fullFilter.begin()._Ptr;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	bool bValid = GetOpenFileNameA(&ofn) != 0;

	if (bValid) outPath = std::string(outPathCStr);

    return bValid;
}
