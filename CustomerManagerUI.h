#pragma once
#include "Action.h"
#include "CustomerTypes.h"
#include "Date.h"
#include "CustomerManager.h"
#include "OutputFactory.h"
#include<string>


class CustomerManagerUI
{
private:
   CustomerManager& manager;
   ConsoleOutput& output;
   Logger& logger;

   
public:
   CustomerManagerUI(CustomerManager& manager, ConsoleOutput& output, Logger& logger) : manager(manager), output(output), logger(logger) {};

   Action Run();
   void ShowMenu();

   Customer CreateCustomer();

   std::string ReadText(const std::string& question);
   int ReadDay();
   int ReadMonth();
   int ReadYear();
   int ReadInt(const std::string& question);
   Date ReadDate(const std::string& question);
   Gender ReadGender(const std::string& question);
   CustomerStatus ReadCustomerStatus(const std::string& question);
   MemberLevel ReadMemberLevel(const std::string& question);
   Action ReadChoice(const std::string& question);
   Action ReadOption(const std::string& question);

   void HandleAdd();
   void HandleUpdate();
   void HandleRemove();
   void Show();
   void Help();
   void Exit();

};

