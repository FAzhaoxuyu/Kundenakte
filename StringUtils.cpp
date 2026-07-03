#include "StringUtils.h"


std::vector<std::string> StringUtils::SplitLine (const std::string& text, char delimiter)
{
   std::vector<std::string> result;
   std::stringstream ss (text);
   std::string part;
   while (std::getline (ss, part, delimiter)) {
      result.push_back(part);
   }
   return result;
}


 