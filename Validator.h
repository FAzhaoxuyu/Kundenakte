#pragma once
#include "Date.h"
#include "ContactData.h"

class Validator
{
public:
   static bool IsValidSingleName (const std::string& name);
   static bool IsValidName (const std::string& firstName, const std::string& LastName);
   static bool IsLeapYear (int year);
   static int GetDaysInMonth (int month, int year);
   static bool IsValidDate (int day, int month, int year);

   static bool IsValidEmail (const std::string& email);
   static bool IsValidAddress (const std::string& address);
 
   static bool IsValidPhoneNr (const std::string& nr);
   static bool IsValidMobileNr (const std::string& nr);
   static bool IsValidTeleNr (const std::string& nr);

   static bool IsValidContact (ContactData::ContactType type, const std::string& value);
};
