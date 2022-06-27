#include <iostream>
#include <string>

#include "ByteHelper.h"
#include "FileHelper.h"
#include "Buffer.h"

#define IN_RANGE(min, x, max) ((x) >= (min) && (x) <= (max))

void PrintUsage()
{
    printf("\n\n./FileAobDiff.exe <file1path.bin> <file2path.bin> <file1offset> <file2offset> <aobdifflen>\n\n");
    exit(1);
}

int main(uint32_t argc, const char* argv[])
{
    if (argc == 6)
    {
        if (FileHelper::FileExist(argv[1]) && FileHelper::FileExist(argv[2]))
        {
            Buffer file1, file2;

            if (FileHelper::ReadFile(argv[1], file1) && FileHelper::ReadFile(argv[2], file2))
            {
                uintptr_t file1Offset = (uintptr_t)strtoll(argv[3], nullptr, 16);
                uintptr_t file2Offset = (uintptr_t)strtoll(argv[4], nullptr, 16);
                uintptr_t bytesToDiff = atoi(argv[5]);

                if (IN_RANGE(0, file1Offset + bytesToDiff, file1.mSize) && IN_RANGE(0, file2Offset + bytesToDiff, file2.mSize))
                {
                    std::string comparationResult = "";
                    std::string qMark = std::string("?");

                    for (size_t i = 0; i < bytesToDiff; i++)
                    {
                        unsigned char sampleCurr = file1.mBuff[file1Offset + i];

                        comparationResult += i == 0 ? "" : " ";

                        if (file1.mBuff[file1Offset + i] == file2.mBuff[file2Offset + i]) comparationResult += ByteHelper::Byte2String(sampleCurr);
                        else comparationResult += qMark;
                    }

                    printf("\n%s\n", comparationResult.c_str());
                }
                else
                {
                    printf("Comparation Out of range.\n");
                    return 3;
                }
            }
            else
            {
                printf("Unable to read One of the files.\n");
                return 2;
            }
        }
        else
        {
            printf("One of the files doesnt exist.\n");
            return 1;
        }
    }
    else PrintUsage();

    return 0;
}