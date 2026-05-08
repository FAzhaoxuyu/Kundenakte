#include "Validator.h"
#include "Date.h"
#include<string>
using namespace std;

bool Validator::IsValidSingleName(const std::string& name)
{
   if (name.empty()) {
      return false;
   }
   for (char ch : name) {
      if (!isalpha(static_cast<char>(ch)) && ch != '-' && ch != ' ') {
         return false;
      }
   }
   return true;
}

bool Validator::IsValidName(const std::string& firstName, const std::string& lastName)
{
   return IsValidSingleName(firstName) && IsValidSingleName(lastName);
}
bool Validator::IsValidEmail(const std::string& email)
{
   if (email.empty())
   {
      return false;
   }

   size_t atPosition = email.find('@');

   if (atPosition == std::string::npos)
   {
      return false;
   }

   if (atPosition == 0)
   {
      return false;
   }

   if (atPosition == email.length() - 1)
   {
      return false;
   }

   size_t dotPosition = email.find('.', atPosition);

   if (dotPosition == std::string::npos)
   {
      return false;
   }

   if (dotPosition == atPosition + 1)
   {
      return false;
   }

   if (dotPosition == email.length() - 1)
   {
      return false;
   }

   return true;
}

bool Validator::IsLeapYear(int year)
{
   return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Validator::GetDaysInMonth(int month, int year)
{
   switch (month)
   {
   case 1: return 31;
   case 2: return IsLeapYear(year) ? 29 : 28;
   case 3: return 31;
   case 4: return 30;
   case 5: return 31;
   case 6: return 30;
   case 7: return 31;
   case 8: return 31;
   case 9: return 30;
   case 10: return 31;
   case 11: return 30;
   case 12: return 31;
   default: return 0;
   }
}

bool Validator::IsValidDate(int day, int month, int year)
{

   if (year < 1900 || year > 2100)
   {
      return false;
   }

   if (month < 1 || month > 12)
   {
      return false;
   }

   int maxDay = GetDaysInMonth(month, year);
   if (day < 1 || day > maxDay)
   {
      return false;
   }

   return true;
}

bool Validator::IsValidAddress(const string& address)
{
   if (address.empty())
   {
      return false;
   }

   if (address.length() < 5)
   {
      return false;
   }

   for (char c : address)
   {
      if (!std::isalnum(static_cast<unsigned char>(c)) &&
         c != ' ' &&
         c != ',' &&
         c != '.' &&
         c != '-' &&
         c != '/')
      {
         return false;
      }
   }

   return true;
}