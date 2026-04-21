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
      ShowMenu();
      Action option = ReadOption("Please choose an option: ");
      switch (option)
      {
         case Action::Add:
         {
            HandleAdd();
            break;
         }
         case Action::Update:
         {
            HandleUpdate();
            break;
         }
         case Action::Remove:
         {
            HandleRemove();
            break;
         }
         case Action::Show:
         {
            Show();
            break;
         }
         case Action::Help:
         {
            Help();
            break;
         }
         case Action::Exit:
         {
            Exit();
            return option;
         }
         
      }

   }
   
}
void CustomerManagerUI::Show()
{
   const std::vector<Customer>& customers = manager.GetCustomers();
   if (manager.GetCustomers().empty()) {
      cout << endl;
      cout << "No customer is available, please add new customer first" << endl;
      return;
   }
   for (const Customer& customer : customers)
   {
      cout << customer.GetId() << " "
         << customer.GetFirstName() << " "
         << customer.GetLastName() << " "
         << customer.GetDateOfBirth().ToString() << " "
         << ToString(customer.GetGender()) << " "
         << ToString(customer.GetMemberLevel()) << " "
         << customer.GetEmail() << " "
         << customer.GetAddress() << " "
         << endl;
   }
}

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

void CustomerManagerUI :: HandleAdd()
{
   cout << endl;
   Customer customer = CreateCustomer();
   manager.Add(customer);
   std::cout << "A new customer added." << std::endl;
}
void CustomerManagerUI :: HandleUpdate()
{
   if (manager.IsEmpty()) {
      cout << endl;
      cout << "No customer is available, please add new customer first" << endl;
      return;
   }
   int id = ReadInt("Please enter customer id: ");
   int option = ReadInt("What do you want to update?\n"
                           "1. First name\n"
                           "2. Last name\n"
                           "3. Birthday\n"
                           "4. Gender\n"
                           "5. Status\n"
                           "6. Member level\n"
                           "7. Email\n"
                           "8. Address\n");
   switch (option)
   {
      case 1: 
      {
         std::string newFirstName = ReadText("Please give a new first name: ");
         manager.UpdateFirstName(id, newFirstName);
         std::cout << "First name updated.\n";
         break;
      }
      case 2:
      {
         std::string newLastName = ReadText("Please give a new last name: ");
         manager.UpdateFirstName(id, newLastName);
         std::cout << "Last name updated.\n";
         break;
      }
      case 3:
      {
         std::string newDateOfBirth = ReadText("Please give a new birthday: ");
         manager.UpdateFirstName(id, newDateOfBirth);
         std::cout << "Date of birth updated.\n";
         break;
      }
      case 4:
      {
         std::string newGender = ReadText("Please give a new gender: ");
         manager.UpdateFirstName(id, newGender);
         std::cout << "Gender updated.\n";
         break;
      }
      case 5:
      {
         std::string newStatus = ReadText("Please give a status: ");
         manager.UpdateFirstName(id, newStatus);
         std::cout << "Customer status updated.\n";
         break;
      }
      case 6:
      {
         std::string newMemberLevel = ReadText("Please give a new member level: ");
         manager.UpdateFirstName(id, newMemberLevel);
         std::cout << "Member level updated.\n";
         break;
      }
      case 7:
      {
         std::string newEmail = ReadText("Please give a new email: ");
         manager.UpdateFirstName(id, newEmail);
         std::cout << "Email updated.\n";
         break;
      }
      case 8:
      {
         std::string newAddress = ReadText("Please give a new Address: ");
         manager.UpdateFirstName(id, newAddress);
         std::cout << "Address updated.\n";
         break;
      }
      default:
      {
         cout << "Invalid choice." << endl;
         break;
      }
   }
}
void CustomerManagerUI::HandleRemove()
{
   if (manager.IsEmpty()) {
      cout << endl;
      cout << "No customer is available, please add new customer first" << endl;
      return;
   }
   int id = ReadInt("Please enter customer id: ");
   manager.RemoveById(id);
}


