#pragma once
#include<iostream>


class Date
{
private:
   int day;
   int month;
   int year;
public:
   Date() = default;
   Date(const int& valDay, const int& valMonth, const int& valYear);

   int getDay()const;
   int getMonth()const;
   int getYear()const;

 //  bool operator == (const Date& other)const;
   std::string DateToString() const;
   static Date StringToDate(const std::string& text);

   void PrintDate();
};