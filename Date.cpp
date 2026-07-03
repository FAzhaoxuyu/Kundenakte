#include "Date.h"
#include "Validator.h"
#include "StringUtils.h"

#include<iostream>
#include<string>
#include<sstream>
using namespace std;


int Date::GetDay () const
{
   return day;
}

int Date::GetMonth () const
{
   return month;
}

int Date::GetYear () const
{
   return year;
}

Date::Date (int valDay, int valMonth, int valYear) : day (valDay), month (valMonth), year (valYear)
{
   if (!Validator::IsValidDate (day, month, year)) {
      throw std::invalid_argument("Invalid date.");
   }
}

string Date::DateToString () const
{
   return to_string(day) + "." + to_string(month) + "." + to_string(year);
}

Date Date::StringToDate (const string& text)
{
   std::vector<string> parts = StringUtils::SplitLine (text, '.');
   
   Date date;
   date.day = std::stoi (parts[0]);
   date.month = std::stoi (parts[1]);
   date.year = std::stoi (parts[2]);
   return date;
}

