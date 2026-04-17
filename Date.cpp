#include "Date.h"
#include<iostream>

#include<string>
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
string Date::ToString() const
{
   return to_string(day) + "." + to_string(month) + "." + to_string(year);
}

void Date::PrintDate()
{
   std::cout << day << "." << month << "." << year << std::endl;
}