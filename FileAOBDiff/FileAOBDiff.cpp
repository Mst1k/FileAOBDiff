#include "FileAOBDiff.h"
#include "DialogManager.h"
#include <string>
#include "FilesEngine.h"
#include "StringHelper.h"
#include <iostream>
#include <conio.h>
#include "Pattern.h"
#include "DiffHelper.h"
#include "PatternEngine.h"
#include <functional>
#include <thread>


FileAOBDiff::FileAOBDiff()
    : pFilesEngine(new FilesEngine())
{
}

FileAOBDiff::~FileAOBDiff()
{
    if (pFilesEngine) delete pFilesEngine;
}

bool FileAOBDiff::Init()
{
    std::string bin1Path;
    std::string bin2Path;

    // Get files path

    if (DialogManager::AskPath("bin1.*", bin1Path) && DialogManager::AskPath("bin2.*", bin2Path)) 
    {
        // Load Files Into Memory

        return pFilesEngine->LoadFile(bin1Path) && pFilesEngine->LoadFile(bin2Path);
    }

    return false;
}

void FileAOBDiff::Run()
{
    if (pFilesEngine->getFilesLoadedCount() >= 2)
    {
        const auto& allFiles = pFilesEngine->getAllFiles();
        const auto* pFile1 = allFiles[0];
        const auto* pFile2 = allFiles[1];
        const auto file1PathTokenized = StringHelper::Tokenize(pFile1->filePathStr, '\\');
        const auto file2PathTokenized = StringHelper::Tokenize(pFile2->filePathStr, '\\');

        while (true)
        {
            uint64_t file1Off;
            uint64_t file2Off;
            int64_t diffingSize;
            std::string file1Name = file1PathTokenized[file1PathTokenized.size() - 1];
            std::string file2Name = file2PathTokenized[file2PathTokenized.size() - 1];

            if (file1Name == file2Name)
            {
                file1Name += "( 1 )";
                file2Name += "( 2 )";
            }

            std::cout << file1Name << " Offset: "; std::cin >> std::hex >> file1Off;
            std::cout << file2Name << " Offset: "; std::cin >> std::hex >> file2Off;
            std::cout << "Enter Diffing Size: "; std::cin >> diffingSize;

            system("cls");

            if (diffingSize > 0)
            {
                if (pFile1->ValidOffset(file1Off) && pFile1->ValidOffset(file1Off + diffingSize) &&
                    pFile2->ValidOffset(file2Off) && pFile2->ValidOffset(file2Off + diffingSize) )
                {
                    Pattern resultDiff;
                    DiffHelper::MakeDiff(pFile1, pFile2, file1Off, file2Off, uint64_t(diffingSize), resultDiff);

                    std::cout << "Result: " << resultDiff.toString() << std::endl;
                    std::vector<uintptr_t> resultDiffFile1Ocurrences;
                    std::vector<uintptr_t> resultDiffFile2Ocurrences;

                    std::thread t1([&] {
                        PatternEngine::FindPattern(pFile1, resultDiff, resultDiffFile1Ocurrences);
                    });

                    std::thread t2([&] {
                        PatternEngine::FindPattern(pFile2, resultDiff, resultDiffFile2Ocurrences);
                    });

                    t1.join();
                    t2.join();

                    if (resultDiffFile1Ocurrences.size() != resultDiffFile2Ocurrences.size())
                    {
                        std::cout << file1Name << ": " << resultDiffFile1Ocurrences.size() << " Ocurrences\n";
                        std::cout << file2Name << ": " << resultDiffFile2Ocurrences.size() << " Ocurrences\n";
                    }
                    else std::cout << "Pattern Unique!\n";                    
                }
                else std::cout << "Invalid Offset\n";
            }
            else std::cout << "Invalid Diffing Size\n";

            _getch();
            system("cls");
        }
    }
    
}
