#include "ContactMethod.h"

#include <string>
#include <sstream>
#include "Algorithm"


ContactType StringToContactTypes(std::string type)
{
   std::transform(type.begin(), type.end(), type.begin(), ::tolower);

   if (type == "mobile") return ContactType::Mobile;
   if (type == "landline") return ContactType::Landline;
   if (type == "email") return ContactType::Email;
   if (type == "other") return ContactType::Other;
   return ContactType::Other;
}

PreferredContactType StringToPreferredContactType(std::string type)
{
   std::transform(type.begin(), type.end(), type.begin(), ::tolower);
   if (type == "none") return PreferredContactType::None;
   if (type == "mobile") return PreferredContactType::Mobile;
   if (type == "landline") return PreferredContactType::Landline;
   if (type == "email") return PreferredContactType::Email;
   if (type == "post") return PreferredContactType::Post;
   if (type == "other") return PreferredContactType::Other;

   throw std::invalid_argument(type);
}

std::string Address::ToString() const
{
   return street + " "
      + HouseNr + ", "
      + postCode + " "
      + city + ", "
      + country;
}

Address Address::StringToAddress(const std::string& text)
{
   Address addr;

   std::stringstream ss(text);
   std::string part1, part2, part3;

   std::getline(ss, part1, ','); // street + HouseNr
   std::getline(ss, part2, ','); // postCode + city
   std::getline(ss, part3);      // country

   std::stringstream s1(part1);
   s1 >> addr.street >> addr.HouseNr;

   std::stringstream s2(part2);
   s2 >> addr.postCode >> addr.city;

   addr.country = part3;

   return addr;
}

std::string PreferredContactTypeToString(PreferredContactType type)
{
   switch (type)
   {
   case PreferredContactType::None: return "None";
   case PreferredContactType::Mobile: return "Mobile";
   case PreferredContactType::Landline: return "Landline";
   case PreferredContactType::Email: return "Email";
   case PreferredContactType::Post: return "Post";
   case PreferredContactType::Other: return "Other";
   default: return "Unknown";
   }
}