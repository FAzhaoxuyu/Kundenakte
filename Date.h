#pragma once
#include<iostream>
#include "OutputFactory.h"


class Date
{
private:
   int day = 0;
   int month = 0;
   int year = 0;
public:
   Date () = default;
   Date (int valDay, int valMonth, int valYear);

   int GetDay ()const;
   int GetMonth ()const;
   int GetYear ()const;

 //  bool operator == (const Date& other) const;
   std::string DateToString () const;
   static Date StringToDate (const std::string& text);

   //void PrintDate ();
};