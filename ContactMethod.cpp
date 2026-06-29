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

ContactType StringToContactType(std::string type)
{
   std::transform(type.begin(), type.end(), type.begin(), ::tolower);
   if (type == "none") return ContactType::None;
   if (type == "mobile") return ContactType::Mobile;
   if (type == "landline") return ContactType::Landline;
   if (type == "email") return ContactType::Email;
   if (type == "post") return ContactType::Post;
   if (type == "other") return ContactType::Other;

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

std::string ContactTypeToString(ContactType type)
{
   switch (type)
   {
   case ContactType::None: return "None";
   case ContactType::Mobile: return "Mobile";
   case ContactType::Landline: return "Landline";
   case ContactType::Email: return "Email";
   case ContactType::Post: return "Post";
   case ContactType::Other: return "Other";
   default: return "Unknown";
   }
}