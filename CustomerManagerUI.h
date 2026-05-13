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
   Output& logOutput;
   Output& consoleOutput;
   Output& multiOutput;

public:
   CustomerManagerUI(CustomerManager& manager, Output& logOutput, Output& consoleOutput, Output& multiOutput) : manager(manager), logOutput(logOutput), consoleOutput(consoleOutput), multiOutput(multiOutput) {};

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

   std::string ReadValidatedFirstName();
   std::string ReadValidatedLastName();
   Date ReadValidatedDate();
  
   std::string ReadValidatedEmail();
   std::string ReadValidatedAddress();

   void HandleAdd();

   void HandleUpdateFirstName(int id);
   void HandleUpdateLastName(int id);
   void HandleUpdateDateOfBirth(int id);
   void HandleUpdateGender(int id);
   void HandleDeactivateCustomer(int id);
   void HandleUpdateMemberLevel(int id);
   void HandleUpdateEmail(int id);
   void HandleUpdateAddress(int id);



   int ReadUpdateOption();
   void HandleUpdate();
   void HandleRemove();
   void Show();
   void Help();
   void Exit();

};

