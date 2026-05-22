#include"OutputFactory.h"
#include<iostream>
#include<fstream>
#include<chrono>
#include <format>
#include <iomanip>
#include <sstream>
#include <ctime>

void ConsoleOutput::Print (const std::string& message) const
{
   std::cout << message;
}
void LogOutput::Print (const std::string& message) const
{
   std::ofstream fs (fileName, std::ios::app);
   if (!fs) {
      return;
   }
   fs << message << '\n';
}

void MultiOutput::Print (const std::string& message) const
{
   consoleOutput.Print(message);
   logOutput.Print(message);
}

void TimeStampDecorator::Print(const std::string& message) const
{
   auto now = std::chrono::system_clock::now();
   std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

   std::tm localTime;
   localtime_s(&localTime, &currentTime);
   std::ostringstream oss;
   oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
   output.Print("[" + oss.str() + "] " + message);
}
void ErrorDecorator::Print(const std::string& message) const
{ 
   output.Print("[ERROR] " + message);
}