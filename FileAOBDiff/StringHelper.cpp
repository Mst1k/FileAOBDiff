#include "StringHelper.h"

std::vector<std::string> StringHelper::Tokenize(std::string str, char delim)
{
    std::vector<std::string> tokens;
    std::string currToken = "";

    for (char c : str)
    {
        if (c == delim)
        {
            tokens.push_back(currToken);
            currToken.clear();
        }
        else currToken += c;
    }

    tokens.push_back(currToken);

    return tokens;
}
