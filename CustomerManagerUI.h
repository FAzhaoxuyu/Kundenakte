#pragma once
#include "Action.h"
#include "CustomerTypes.h"
#include "Date.h"
#include "CustomerManager.h"
#include "OutputFactory.h"
#include "ContactMethod.h"

#include<string>


class CustomerManagerUI
{
private:
   CustomerManager& manager;
   Output& logOutput;
   Output& consoleOutput;
   Output& multiOutput;
   Output& errorLogger;

   int selectedCustomerID = -1;

public:
   CustomerManagerUI (CustomerManager& manager, Output& logOutput, Output& consoleOutput, Output& multiOutput, Output& errorLogger) : manager(manager), logOutput(logOutput), consoleOutput(consoleOutput), multiOutput(multiOutput), errorLogger(errorLogger) {};

   void Run ();
   void ShowMenu ();

   Customer CreateCustomer ();

   std::string ReadText (const std::string& question);
   int ReadDay ();
   int ReadMonth ();
   int ReadYear ();
   int ReadInt (const std::string& question);
   Date ReadDate (const std::string& question);
   customerTypes::Gender ReadGender (const std::string& question);
   customerTypes::CustomerStatus ReadCustomerStatus (const std::string& question);
   customerTypes::MemberLevel ReadMemberLevel (const std::string& question);
   Action ReadChoice (const std::string& question);
   Action ReadOption (const std::string& question);

   std::vector<std::string> ReadPhoneNrs();
   std::vector<std::string> ReadMobileNrs();
   std::vector<std::string> ReadTeleNrs();
   //std::vector<std::string> ReadEmails();
   ContactType ReadContactType();
   ContactType ReadPrefer();

   std::string ReadValidatedFirstName ();
   std::string ReadValidatedLastName ();
   Date ReadValidatedDate ();
  
   std::string ReadValidatedEmail ();
   std::string ReadValidatedAddress ();

   Contact ReadContact();
   Contact ReadValidContact();

   ContactType ReadPreferredContactMethod();

   void HandleAdd ();
   void HandleSelect();
   bool HasSelectedCustomer() const;

   void HandleUpdateFirstName ();
   void HandleUpdateLastName ();
   void HandleUpdateDateOfBirth ();
   void HandleUpdateGender ();
   void HandleDeactivateCustomer ();
   void HandleUpdateMemberLevel ();
   void HandleUpdateEmail ();
   void HandleUpdateAddress ();

   void HandleUpdateSelectedCustomer();
   void HandleRemoveSelectedCustomer();
   void HandleShowSelectedCustomer();

   int ReadUpdateOption ();

   void ShowMainMenu ();
   void ShowCustomerMenu ();
   void HandleCustomerMenu ();
   void HandleUpdateCustomer ();


   void Show ();
   void Help ();
   void Exit ();

};

