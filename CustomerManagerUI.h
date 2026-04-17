#pragma once
#include "Action.h"
#include "CustomerTypes.h"
#include "Date.h"
#include "CustomerManager.h"
#include<string>


class CustomerManagerUI
{
private:
   CustomerManager manager;
   
public:
   Action Run();
   void ShowMenu();

   Customer CreateCustomer();

    std::string ReadText(const std::string& quesiton);
    int ReadInt(const std::string& question);
    Date ReadDate(const std::string& question);
    Gender ReadGender(const std::string& question);
    CustomerStatus ReadCustomerStatus(const std::string& question);
    MemberLevel ReadMemberLevel(const std::string& question);
    Action ReadChoice(const std::string& question);
    Action ReadOption(const std::string& question);

   void Help();
   void Exit();

 /*  void ShowCustomerList();*/

};

