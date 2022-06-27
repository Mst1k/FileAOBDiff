#include "DiffHelper.h"
#include "File.h"
#include "Buffer.h"
#include "Pattern.h"

void DiffHelper::MakeDiff(const File* pFile1, const File* pFile2, uint64_t off1, uint64_t off2, uint64_t diffSize, Pattern& outPatternResult)
{
    const auto* pFile1RawBuff = pFile1->pBuff->mBuff;
    const auto* pFile2RawBuff = pFile2->pBuff->mBuff;

    for (size_t i = 0; i < diffSize; i++)
    {
        auto sample1Byte = pFile1RawBuff[off1 + i];

        if (sample1Byte == pFile2RawBuff[off2 + i]) outPatternResult.AddByte(sample1Byte, false);
        else  outPatternResult.AddWildCard();
    }
}
