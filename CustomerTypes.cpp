#include "CustomerTypes.h"
#include<string>
#include<stdexcept>
#include<iostream>
using namespace std;

string customerTypes::GenderToString (customerTypes::Gender gender)
{
   switch (gender)
   {
   case customerTypes::Gender::Male: return "Male";
   case customerTypes::Gender::Female: return "Female";
   case customerTypes::Gender::Diverse: return "Diverse";
   default: return "Unknown";
   }
}
string customerTypes::StatusToString (customerTypes::CustomerStatus customerStatus)
{
   switch (customerStatus)
   {
   case customerTypes::CustomerStatus::Active: return "Active";
   case customerTypes::CustomerStatus::Inactive: return "Inactive";
   default: return "Unknown";
   }
}
string customerTypes::LevelToString (customerTypes::MemberLevel memberLevel)
{
   switch (memberLevel)
   {
   case customerTypes::MemberLevel::Standard: return "Standard";
   case customerTypes::MemberLevel::Private: return "Private";
   case customerTypes::MemberLevel::Premium: return "Premium";
   case customerTypes::MemberLevel::Corporate: return "Corporate";
   default: return "Unknown";
   }
}

customerTypes::Gender customerTypes::StringToGender (const std::string& text)
{
   if (text == "Male") {
      return customerTypes::Gender::Male;
   }
   else if (text == "Female") {
      return customerTypes::Gender::Female;
   }
   else if (text == "Diverse") {
      return customerTypes::Gender::Diverse;
   } 
   throw std::invalid_argument("Unknown gender: " + text);
}
customerTypes::CustomerStatus customerTypes::StringToStatus (const std::string& text)
{
   if (text == "Active") {
      return customerTypes::CustomerStatus::Active;
   }
   else {
      return customerTypes::CustomerStatus::Inactive;
   }
}
customerTypes::MemberLevel customerTypes::StringToLevel (const std::string& text)
{
   if (text == "Standard") {
      return customerTypes::MemberLevel::Standard;
   }
   else if (text == "Private") {
      return customerTypes::MemberLevel::Private;
   }
   else if (text == "Premium") {
      return customerTypes::MemberLevel::Premium;
   }
   else {
      return customerTypes::MemberLevel::Corporate;
   }
}
