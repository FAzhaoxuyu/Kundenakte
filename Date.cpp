#include "Date.h"
#include "Validator.h"
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

Date::Date (int valDay, int valMonth, int valYear):day(valDay), month(valMonth), year(valYear)
{
   if (!Validator::IsValidDate(day, month, year)) {
      throw std::invalid_argument("Invalid date.");
   }
}
//bool Date::operator == (const Date& other)const
//{
//   return this->day == other.day && this->month == other.month && this->year == other.year;
//}
string Date::DateToString () const
{
   return to_string(day) + "." + to_string(month) + "." + to_string(year);
}

Date Date::StringToDate (const string& text)
{
   Date date;
   date.day = std::stoi(text.substr(0, 2));
   date.month = std::stoi(text.substr(3, 2));
   date.year = std::stoi(text.substr(6, 4));
   return date;
   //std::stringstream ss(text);
   //std::string dayStr;
   //std::string monthStr;
   //std::string yearStr;

   //std::getline(ss, dayStr, '.');
   //int day = std::stoi(dayStr);

   //std::getline(ss, monthStr, '.');
   //int month = std::stoi(monthStr);

   //std::getline(ss, yearStr, '.');
   //int year = std::stoi(yearStr);

   

}

//void Date::PrintDate ()
//{
//   std::cout << day << "." << month << "." << year << std::endl;
//   output.Print()
//}