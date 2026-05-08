#include "Date.h"
#include "Action.h"
#include "Customer.h"
#include "CustomerManager.h"
#include "CustomerManagerUI.h"
#include "CustomerRepository.h"
#include "OutputFactory.h"
#include "Validator.h"
#include <iostream>

using namespace std;


void CustomerManagerUI::ShowMenu()
{
   output.Print("===== Customer Management =====\n");
   output.Print("1: Add\n");
   output.Print("2: Update\n");
   output.Print("3: Remove\n");
   output.Print("4: Show\n");
   output.Print("5: Help\n");
   output.Print("6: Exit\n");
   output.Print("===============================\n");
}
string CustomerManagerUI::ReadText(const string& question)
{
   while (true)
   {
      output.Print(question);
      string input;
      getline(cin, input);
      if (!input.empty())
      {
         return input;
      }
      output.Print("Invalid input, please enter agian.\n");
   }
}

int CustomerManagerUI::ReadDay()
{
   while (true)
   {
      int day = ReadInt("Day: ");
      if (day >= 1 && day <= 31)
      {
         return day;
      }
      output.Print("Invalid day.\n");
   }
}

int CustomerManagerUI::ReadMonth()
{
   while (true)
   {
      int month = ReadInt("Month: ");
      if (month >= 1 && month <= 12)
      {
         return month;
      }
      output.Print("Invalid month.\n");
   }
}

int CustomerManagerUI::ReadYear()
{
   while (true)
   {
      int year = ReadInt("Year: ");
      if (year >= 1900 && year <= 2100)
      {
         return year;
      }
      output.Print("Invalid year.\n");
   }
}

int CustomerManagerUI::ReadInt(const string& question)
{
   while (true)
   {
      output.Print(question);
      string input;
      getline(cin, input);
 
      try {
         int Number = stoi(input);
         return Number;
      }
      catch (const std::exception&) {
         output.Print("Invalid input, please enter a number.\n");
      }
   }
}

Date CustomerManagerUI::ReadDate(const string& question)
{
   while (true)
   {
      try
      {
         int day = ReadDay();
         int month = ReadMonth();
         int year = ReadYear();
         return Date(day, month, year);
      }
      catch(const std::exception&){
         output.Print("Invalid input, please enter again.\n");
      }
   }
}

Gender CustomerManagerUI::ReadGender(const string& question)
{
   while (true) {
      int choice = ReadInt("Please choose gender: 1.Male / 2.Female /3.Diverse: ");
      switch (choice)
      {
      case 1: return Gender::Male;
      case 2: return Gender::Female;
      case 3: return Gender::Diverse;
      default: output.Print("Invalid input, please choose again.\n");
         break;
      }
   }
}

MemberLevel CustomerManagerUI::ReadMemberLevel(const string& question)
{
   while (true)
   {
      int choice = ReadInt(question);

      switch (choice)
      {
      case 1: return MemberLevel::Standard;
      case 2: return MemberLevel::Private;
      case 3: return MemberLevel::Premium;
      case 4: return MemberLevel::Corporate;
      default:
         output.Print("Invalid member level, please enter again.\n");
      }
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
   if (!manager.HasCustomers()) {
      output.Print("\n");
      output.Print("No customer is available, please add new customer first.\n") ;
      return;
   }
   for (const Customer& customer : customers)
   {
      output.Print(customer.CustomerToString() + "\n");
   }
}

Action CustomerManagerUI::ReadOption(const string& question)
{
   while (true) {
      output.Print(question);
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
      default: output.Print("Invalid input, please choose an option again.");
      }
   }
}

Customer CustomerManagerUI::CreateCustomer()
{
   int id = manager.GenerateCustomerId();

   string firstName;
   while (true)
   {
      firstName = ReadText("First name: ");
      if (!Validator::IsValidSingleName(firstName))
      {
         output.Print("Invalid firstNname, please enter again.\n");
         continue;
      }
      break;
   }

   string lastName;
   while (true)
   {
 
      lastName = ReadText("Last name: ");
      if (!Validator::IsValidSingleName(lastName))
      {
         output.Print("Invalid  last name, please enter again.\n");
         continue;
      }
      break;
   }

   Date dateOfBirth = ReadDate("Please enter the date of birth: ");

   Gender gender = ReadGender("Gender (1.Male / 2.Female / 3.Diverse): ");
   CustomerStatus customerStatus = CustomerStatus::Active;
   MemberLevel memberLevel = ReadMemberLevel("Member level (1.Standard / 2.Private / 3.Premium / 4. Corporate): ");
   
   string email;
   while (true)
   {
      email = ReadText("Please enter email: ");
      if (!Validator::IsValidEmail(email))
      {
         output.Print("Invalid email.\n");
         continue;
      }
      break;
   }

   string address;
   while (true)
   {
      address = ReadText("Please enter address: ");
      if (!Validator::IsValidAddress(address))
      {
         output.Print("Invalid address.\n");
         continue;
      }
      break;

   }
   
   Customer newCustomer = Customer(id, firstName, lastName, dateOfBirth, gender);
   newCustomer.SetCustomerStatus(customerStatus);
   newCustomer.SetMemberLevel(memberLevel);
   newCustomer.SetEmail(email);
   newCustomer.SetAddress(address);

   return newCustomer;
}


void CustomerManagerUI::Help()
{
   //std::unique_ptr<Output> output = std::make_unique<ConsoleOutput>();

   output.Print("== Help page ==== = \n");
   output.Print("1. Add: Create a new customer to the system.\n");
   output.Print("2. Update: Change or update customer information.\n");
   output.Print("3. Remove: Remove a customer.\n");
   output.Print("4. Show: Show current customer list.\n");
   output.Print("5. Help: Show explanation of every menu option.\n");
   output.Print("6: Exit: Close the program.\n");  
}
void CustomerManagerUI::Exit()
{
   //std::unique_ptr<Output> output = std::make_unique<ConsoleOutput>();

   output.Print("Exit called\n");
   output.Print("Program closed.");
}

void CustomerManagerUI :: HandleAdd()
{
   Customer customer = CreateCustomer();
   manager.Add(customer);
   output.Print("A new customer added.");
   logger.Print("A new customer added.\n");
}
void CustomerManagerUI :: HandleUpdate()
{
   if (!manager.HasCustomers()) {
      output.Print("No customer is available, please add new customer first.\n");
      logger.Print("No customer is available, please add new customer first.\n");

      return;
   }
   int id = ReadInt("Please enter customer id: ");
   if (!manager.CustomerExists(id))
   {
      output.Print("customer not found.");
      logger.Print("customer not found.");
   }
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
         if (!Validator::IsValidSingleName(newFirstName)) {
            output.Print("Invalid first name.\n");
            return;
         }
         manager.UpdateFirstName(id, newFirstName);
         output.Print("First name updated.\n");
         logger.Print("First name updated.\n");
         break;
      }
      case 2:
      {
         std::string newLastName = ReadText("Please give a new last name: ");
         if (!Validator::IsValidSingleName(newLastName)) {
            output.Print("Invalid first name.\n");
            return;
         }
         manager.UpdateLastName(id, newLastName);
         output.Print("Last name updated.\n");
         logger.Print("Last name updated.\n");
         break;
      }
      case 3:
      {
         Date newDateOfBirth = ReadDate("Please give a new birthday: ");
         manager.UpdateDateOfBirth(id, newDateOfBirth);
         output.Print("Date of birth updated.\n");
         logger.Print("Date of birth updated.\n");
         break;
      }
      case 4:
      {
         Gender newGender = ReadGender("Please give a new gender: ");
         manager.UpdateGender(id, newGender);
         output.Print("Gender updated.\n");
         logger.Print("Gender updated.\n");
         break;
      }
      case 5:
      {
         CustomerStatus newStatus = CustomerStatus::Inactive;
         if (!manager.UpdateStatus(id, newStatus))
         {
            output.Print("Customer not found.\n");
            logger.Print("Update status failed: customer not found.");
            break;
         }

         output.Print("Customer deactivated.\n");
         logger.Print("Customer deactivated.");
         break;
      }
      case 6:
      {
         MemberLevel newMemberLevel = ReadMemberLevel("Please give a new member level (1.Standard / 2.Private / 3.Premium / 4. Corporate): ");
         manager.UpdateMemberLevel(id, newMemberLevel);
         output.Print("Member level updated.\n");
         logger.Print("Member level updated.\n");
         break;
      }
      case 7:
      {
         std::string newEmail = ReadText("Please give a new email: ");
         if (!Validator::IsValidEmail(newEmail)) {
            output.Print("Invalid email format.\n");
            logger.Print("Invalid email format entered while updating customer information.\n");
            break;
         }

         if (manager.UpdateEmail(id, newEmail)) {
            output.Print("Email updated.\n");
            logger.Print("Email updated.\n");
         }
         break;
      }
      case 8:
      {
         std::string newAddress = ReadText("Please give a new Address: ");
         if (!Validator::IsValidAddress(newAddress)) {
            output.Print("Invalid address format.\n");
            logger.Print("Invalid address format entered while updating customer information.\n");
            break;
         }
         if (manager.UpdateAddress(id, newAddress)) {
            output.Print("Address updated.\n");
            logger.Print("Address updated.\n");
         }
         break;
      }
      default:
      {
         output.Print("Invalid choice.");        
         break;
      }
   }
}
void CustomerManagerUI::HandleRemove()
{
   if (manager.HasCustomers()) {
      output.Print("\n");
      output.Print("No customer is available, please add new customer first");
      return;
   }
   int id = ReadInt("Please enter customer id: ");
   manager.RemoveById(id);
   logger.Print("Customer removed.\n");
}

