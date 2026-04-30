#include "CustomerTypes.h"
#include<string>
#include<stdexcept>
#include<iostream>
using namespace std;

string GenderToString(Gender gender)
{
   switch (gender)
   {
   case Gender::Male: return "Male";
   case Gender::Female: return "Female";
   case Gender::Diverse: return "Diverse";
   default: return "Unknown";
   }
}
string StatusToString(CustomerStatus customerStatus)
{
   switch (customerStatus)
   {
   case CustomerStatus::Active: return "Active";
   case CustomerStatus::Inactive: return "Inactive";
   default: return "Unknown";
   }
}
string LevelToString(MemberLevel memberLevel)
{
   switch (memberLevel)
   {
   case MemberLevel::Standard: return "Standard";
   case MemberLevel::Private: return "Private";
   case MemberLevel::Premium: return "Premium";
   case MemberLevel::Corporate: return "Corporate";
   default: return "Unknown";
   }
}

Gender StringToGender(const std::string& text)
{
   if (text == "Male")
   {
      return Gender::Male;
   }
   else if (text == "Female")
    {
      return Gender::Female;
    }
   else if (text == "Diverse")
    {
      return Gender::Diverse;
    } 
   throw std::invalid_argument("Unknown gender: " + text);
}
CustomerStatus StringToStatus(const std::string& text)
{
   if (text == "Active")
   {
      return CustomerStatus::Active;
   }
   else
   {
      return CustomerStatus::Inactive;
   }
}
MemberLevel StringToLevel(const std::string& text)
{
   if (text == "Standard")
   {
      return MemberLevel::Standard;
   }
   else if (text == "Private")
   {
      return MemberLevel::Private;
   }
   else if (text == "Premium")
   {
      return MemberLevel::Premium;
   }
   else
   {
      return MemberLevel::Corporate;
   }
}
