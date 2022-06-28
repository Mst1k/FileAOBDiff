#pragma once

class FilesEngine;

class FileAOBDiff
{
private:
	FilesEngine* pFilesEngine;

public:
	FileAOBDiff();
	~FileAOBDiff();

	bool Init();
	void Run();
};

