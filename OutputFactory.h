#pragma once
#include<string>

class Output
{
public:
   virtual void Print(const std::string& messaage) const = 0;
};

class ConsoleOutput : public Output
{
public:
   void Print(const std::string& messsage) const override;
};

class Logger : public Output
{
public:
   Logger(const std::string& valFileName) : fileName(valFileName) {};
   void Print(const std::string& messsage) const override;

private:
   std::string fileName;
};