#include "InputParser.hpp"
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

std::string getCmdOption(std::vector<std::string> &tokens, const std::string &option)
{
    //std::vector<std::string>::const_iterator itr;
    auto itr = std::find(tokens.begin(), tokens.end(), option);
    if(itr != tokens.end() && ++itr != tokens.end())
    {
        return *itr;
    }
    static const std::string empty_string("");
    return empty_string;
}
