#pragma once
#include<vector>
#include<string>
#include<sstream>
class StringUtils
{
public:
   static std::vector<std::string> SplitLine (const std::string& text, char delimiter);
};
