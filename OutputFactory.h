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

class LogOutput : public Output
{
public:
   LogOutput(const std::string& valFileName) : fileName(valFileName) {};
   void Print(const std::string& messsage) const override;

private:
   std::string fileName;
};

class MultiOutput : public Output
{
public:
   MultiOutput(Output& console, Output& logger) : consoleOutput(console), logOutput(logger) {};
   void Print(const std::string& message) const override;
private:
   Output& consoleOutput;
   Output& logOutput;
};