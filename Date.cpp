#include "Date.h"
#include<iostream>
#include<string>
#include<sstream>
using namespace std;

Date::Date(const int& valDay, const int& valMonth, const int& valYear) : day{ valDay }, month{ valMonth }, year{ valYear } {};

int Date::getDay()const
{
   return day;
}
int Date::getMonth()const
{
   return month;
}
int Date::getYear()const
{
   return year;
}

//bool Date::operator == (const Date& other)const
//{
//   return this->day == other.day && this->month == other.month && this->year == other.year;
//}
string Date::DateToString() const
{
   return to_string(day) + "." + to_string(month) + "." + to_string(year);
}

Date Date::StringToDate(const string& text)
{
   std::stringstream ss(text);
   std::string dayStr;
   std::string monthStr;
   std::string yearStr;

   std::getline(ss, dayStr, '.');
   int day = std::stoi(dayStr);

   std::getline(ss, monthStr, '.');
   int month = std::stoi(monthStr);

   std::getline(ss, yearStr, '.');
   int year = std::stoi(yearStr);

   return Date (day, month, year);

}

void Date::PrintDate()
{
   std::cout << day << "." << month << "." << year << std::endl;
}