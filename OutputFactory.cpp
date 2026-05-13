#include"OutputFactory.h"
#include<iostream>
#include<fstream>
#include<chrono>
#include <format>

void ConsoleOutput::Print(const std::string& message) const
{
   std::cout << message;
}
void LogOutput::Print(const std::string& message) const
{
   std::ofstream fs(fileName, std::ios::app);
   if (!fs) {
      return;
   }

   auto now = std::chrono::system_clock::now();
   std::time_t time = std::chrono::system_clock::to_time_t(now);

   std::tm localTime;
   localtime_s(&localTime, &time);

   fs << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S")
      << " - "
      << message
      << '\n';
}

void MultiOutput::Print(const std::string& message) const
{
   consoleOutput.Print(message);
   logOutput.Print(message);
}