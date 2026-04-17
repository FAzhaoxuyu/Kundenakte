#include "Date.h"
#include "Action.h"
#include "Customer.h"
#include "CustomerManager.h"
#include "CustomerManagerUI.h"
#include <iostream>

using namespace std;


void CustomerManagerUI::ShowMenu()
{
   std::cout << "===== Customer Management =====\n";
   std::cout << "1: Add" << std::endl;
   std::cout << "2: Update" << std::endl;
   std::cout << "3: Remove" << std::endl;
   std::cout << "4: Show" << std::endl;
   std::cout << "5: Help" << std::endl;
   std::cout << "6: Exit" << std::endl;
   std::cout << "===============================\n";
}
string CustomerManagerUI::ReadText(const string& question)
{
   cout << question;
   string input;
   getline(cin, input);
   return input;
}

int CustomerManagerUI::ReadInt(const string& question)
{
   cout << question;
   string input;
   getline(cin, input);
   int Number = stoi(input);
   return Number;
}

Date CustomerManagerUI::ReadDate(const string& question)
{
   cout << question;
   int day = ReadInt("Please enter the day of birth: ");
   int month = ReadInt("Please enter the month of birth: ");
   int year = ReadInt("Please enter the year of birth: ");
   return Date(day, month, year);
}

Gender CustomerManagerUI::ReadGender(const string& question)
{
   while (true) {
      cout << question;
      string input;
      getline(cin, input);
      int choice = stoi(input);
      switch (choice)
      {
      case 1: return Gender::Male;
      case 2: return Gender::Female;
      case 3: return Gender::Diverse;
      default: cout << "Invalid input, please choose again.";
         break;
      }
   }
}

CustomerStatus CustomerManagerUI::ReadCustomerStatus(const string& question)
{
   cout << question;
   string input;
   getline(cin, input);
   int choice = stoi(input);
   switch (choice)
   {
   case 1: return CustomerStatus::Active;
   case 2: return CustomerStatus::Inactive;
   default: return CustomerStatus::Active;
      break;
   }
}

MemberLevel CustomerManagerUI::ReadMemberLevel(const string& question)
{
   cout << question;
   string input;
   getline(cin, input);
   int choice = stoi(input);
   switch (choice)
   {
   case 1: return MemberLevel::Standard;
   case 2: return MemberLevel::Private;
   case 3: return MemberLevel::Premium;
   case 4: return MemberLevel::Corporate;
   default: return MemberLevel::Standard;
      break;
   }
}
Action CustomerManagerUI::Run()
{
   while (true)
   {
      bool running = true;

      ShowMenu();
      Action option = ReadOption("Please choose an option: ");
      switch (option)
      {
         case Action::Add:
         {
            Customer customer = CreateCustomer();
            manager.Add(customer);
            break;
         }
         case Action::Update:
         {
            manager.Update();
            break;
         }
         case Action::Remove:
         {
            manager.Remove();
            break;
         }
         case Action::Show:
         {
            manager.Show();
            break;
         }

         case Action::Help:
         {
            Help();
            break;
         }
         case Action::Exit:
         {
            running = false;
            break;
         }
         return option;
      }

   }
   
}
//void CustomerManagerUI::ShowCustomerList()
//{
//   manager.Show();
//}

Action CustomerManagerUI::ReadOption(const string& question)
{
   while (true) {
      cout << question;
      string input;
      getline(cin, input);
      int choice = stoi(input);

      switch (choice)
      {
      case 1: return Action::Add;
      case 2: return Action::Update;
      case 3: return Action::Remove;
      case 4: return Action::Show;
      case 5: return Action::Help;
      case 6: return Action::Exit;
      default: cout << "Invalid input, please choose an option again.";
      }
   }
}

Customer CustomerManagerUI::CreateCustomer()
{
   int id = manager.GenerateCustomerId();
   string firstName = ReadText("Please enter the first name: ");
   string lastName = ReadText("Please enter the last name: ");
   Date dateOfBirth = ReadDate("Please enter the date of birth: ");
   Gender gender = ReadGender("Please enter gender (1.Male / 2.Female / 3.Diverse): ");
   CustomerStatus customerStatus = CustomerStatus::Active;
   MemberLevel memberLevel = ReadMemberLevel("Please choose member level (1.Standard / 2.Private 7 3.Premium / 4. Corporate): ");
   string email = ReadText("Please enter email: ");
   string address = ReadText("Please enter address: ");
   Customer newCustomer = Customer(id, firstName, lastName, dateOfBirth, gender, customerStatus, memberLevel, email, address);
   return newCustomer;
}


void CustomerManagerUI::Help()
{
   std::cout << "\n===== Help page =====\n";

   std::cout << "1. Add: Create a new customer to the system.\n";

   std::cout << "2. Update: Change or update customer information.\n";

   std::cout << "3. Remove: Remove a customer.\n";

   std::cout << "4. Show: Show current customer list.\n";

   std::cout << "5. Help: Show explanation of every menu option.\n";

   std::cout << "6: Exit: Close the program.\n";
   
}
void CustomerManagerUI::Exit() 
{
   std::cout << "Program closed." << std::endl;
}

