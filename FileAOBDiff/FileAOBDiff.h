#pragma once

class FilesEngine;
class PatternEngine;


class FileAOBDiff
{
private:
	FilesEngine* pFilesEngine;
	PatternEngine* pPatternEngine;

public:
	FileAOBDiff();
	~FileAOBDiff();

	bool Init();
	void Run();
};

