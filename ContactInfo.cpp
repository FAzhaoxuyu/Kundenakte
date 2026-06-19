#include "ContactMethod.h"

#include <string>
#include <sstream>


ContactType StringToContactTypes(std::string type)
{
   if (type == "mobile") return ContactType::Mobile;
   if (type == "landline") return ContactType::Landline;
   if (type == "email") return ContactType::Email;
   if (type == "post") return ContactType::Post;
   return ContactType::Other;
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

