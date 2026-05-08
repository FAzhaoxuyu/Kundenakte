#include"OutputFactory.h"
#include<iostream>
#include<fstream>
#include<chrono>
#include <format>

void ConsoleOutput::Print(const std::string& message) const
{
   std::cout << message;
}
void Logger::Print(const std::string& message) const
{
   std::ofstream fs(fileName, std::ios::app);
   if (!fs) {
      return;
   }

   auto now = std::chrono::system_clock::now();
   auto seconds = std::chrono::floor<std::chrono::seconds>(now);
   fs << std::format("{:%Y-%m-%d %H:%M:%S}", seconds)
      << " - "
      << message
      << '\n';
}