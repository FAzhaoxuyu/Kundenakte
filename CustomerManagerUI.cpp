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
   consoleOutput.Print("===== Customer Management =====\n");
   consoleOutput.Print("1: Add\n");
   consoleOutput.Print("2: Update\n");
   consoleOutput.Print("3: Remove\n");
   consoleOutput.Print("4: Show\n");
   consoleOutput.Print("5: Help\n");
   consoleOutput.Print("6: Exit\n");
   consoleOutput.Print("===============================\n");
}
string CustomerManagerUI::ReadText(const string& question)
{
   while (true)
   {
      consoleOutput.Print(question);
      string input;
      getline(cin, input);
      if (!input.empty())
      {
         return input;
      }
      consoleOutput.Print("Invalid input, please enter agian.\n");
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
      consoleOutput.Print("Invalid day.\n");
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
      consoleOutput.Print("Invalid month.\n");
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
      consoleOutput.Print("Invalid year.\n");
   }
}

int CustomerManagerUI::ReadInt(const string& question)
{
   while (true)
   {
      consoleOutput.Print(question);
      string input;
      getline(cin, input);
 
      try {
         int number = stoi(input);
         return number;
      }
      catch (const std::exception&) {
         consoleOutput.Print("Invalid input, please enter a number:\n");
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
         consoleOutput.Print("Invalid member level, please enter again.\n");
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
      consoleOutput.Print("\n");
      consoleOutput.Print("No customer is available, please add new customer first.\n") ;
      return;
   }
   for (const Customer& customer : customers)
   {
      consoleOutput.Print(customer.CustomerToString() + "\n");
   }
}

Action CustomerManagerUI::ReadOption(const string& question)
{
   while (true) {
      consoleOutput.Print(question);
      string input;
      getline(cin, input);

      try
      {
         int choice = stoi (input);

         switch (choice)
         {
         case 1: return Action::Add;
         case 2: return Action::Update;
         case 3: return Action::Remove;
         case 4: return Action::Show;
         case 5: return Action::Help;
         case 6: return Action::Exit;
         default : consoleOutput.Print("Invalid input, please choose an option again.");
         }
      }
      catch (const exception& ex)
      {
         logOutput.Print(std::string("Invalid input: ") + ex.what() + "\n");
         consoleOutput.Print("Invalid input, please enter again.\n");
      }
   }
}

string CustomerManagerUI::ReadValidatedFirstName()
{
   while (true)
   {
      string firstName = ReadText("Please enter a new first name: ");
      if (!Validator::IsValidSingleName(firstName))
      {
         consoleOutput.Print("Invalid firstNname, please enter again.\n");
         continue;
      }
      return firstName;
   }
}

std::string CustomerManagerUI::ReadValidatedLastName()
{
   while (true)
   {
     string  lastName = ReadText("Please enter a new last name: ");
      if (!Validator::IsValidSingleName(lastName))
      {
         consoleOutput.Print("Invalid  last name, please enter again.\n");
         continue;
      }
      return lastName;
   }
}
Date CustomerManagerUI::ReadDate(const std::string& question)
{
   while (true)
   {
      consoleOutput.Print(question + "\n");
      int day = ReadDay();
      int month = ReadMonth();
      int year = ReadYear();

      return Date(day, month, year); 
   }
}

Date CustomerManagerUI::ReadValidatedDate()
{
   while (true) {
      Date date = ReadDate("Please enter date of birth: ");
      if (Validator::IsValidDate(date.GetDay(), date.GetMonth(), date.GetYear())) {
         return date;
      }

      consoleOutput.Print("Invalid input, please enter again.\n");
   }
}

Gender CustomerManagerUI::ReadGender(const string& question)
{
   while (true) {
      consoleOutput.Print(question);

      int choice = ReadInt("Please choose gender: 1.Male / 2.Female /3.Diverse: ");
      switch (choice)
      {
      case 1: return Gender::Male;
      case 2: return Gender::Female;
      case 3: return Gender::Diverse;
      default: consoleOutput.Print("Invalid input, please choose again.\n");
         break;
      }
   }
}


string CustomerManagerUI::ReadValidatedEmail()
{
   while (true) {
     string email = ReadText("Please enter email: ");
      if (!Validator::IsValidEmail(email))
      {
         consoleOutput.Print("Invalid email.\n");
         continue;
      }
      return email;
   }
}
string CustomerManagerUI::ReadValidatedAddress()
{
   while (true)
   {
      string address = ReadText("Please enter address: ");
      if (!Validator::IsValidAddress(address))
      {
         consoleOutput.Print("Invalid address.\n");
         continue;
      }
      return address;
   }
}

Customer CustomerManagerUI::CreateCustomer()
{
   int id = manager.GenerateCustomerId();
   string firstName = ReadValidatedFirstName();
   string lastName = ReadValidatedLastName();
   Date dateOfBirth = ReadValidatedDate(); 
   Gender gender = ReadGender("Gender (1.Male / 2.Female / 3.Diverse): ");
   CustomerStatus customerStatus = CustomerStatus::Active;
   MemberLevel memberLevel = ReadMemberLevel("Member level (1.Standard / 2.Private / 3.Premium / 4. Corporate): ");
   string email = ReadValidatedEmail();
   string address = ReadValidatedAddress();

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

   consoleOutput.Print("== Help page ==== = \n");
   consoleOutput.Print("1. Add: Create a new customer to the system.\n");
   consoleOutput.Print("2. Update: Change or update customer information.\n");
   consoleOutput.Print("3. Remove: Remove a customer.\n");
   consoleOutput.Print("4. Show: Show current customer list.\n");
   consoleOutput.Print("5. Help: Show explanation of every menu option.\n");
   consoleOutput.Print("6: Exit: Close the program.\n");
}
void CustomerManagerUI::Exit()
{
   //std::unique_ptr<Output> output = std::make_unique<ConsoleOutput>();

   consoleOutput.Print("Exit called\n");
   consoleOutput.Print("Program closed.");
}

void CustomerManagerUI :: HandleAdd()
{
   Customer customer = CreateCustomer();
   manager.Add(customer);
   multiOutput.Print("A new customer added.\n");
}

void CustomerManagerUI::HandleUpdateFirstName(int id)
{
   std::string newFirstName = ReadValidatedFirstName();

   if (manager.UpdateFirstName(id, newFirstName)) {
      multiOutput.Print("First name updated.\n");
   }
   else {
      consoleOutput.Print("Customer not found.\n");
      logOutput.Print("Update first name failed: customer not found.\n");
   }
}
void CustomerManagerUI::HandleUpdateLastName(int id)
{
   std::string newLastName = ReadValidatedLastName();
   if (manager.UpdateLastName(id, newLastName)) {
      multiOutput.Print("Last name updated.\n");
   }
   else {
      consoleOutput.Print("Customer not found.\n");
      logOutput.Print("Update last name failed: customer not found.\n");
   }
}
void CustomerManagerUI::HandleUpdateDateOfBirth(int id)
{
   Date newDateOfBirth = ReadValidatedDate();

   if (manager.UpdateDateOfBirth(id, newDateOfBirth)) {
      multiOutput.Print("Date of birth updated.\n");
   }
   else {
      consoleOutput.Print("Customer not found.\n");
      logOutput.Print("Update birthday failed: customer not found.\n");
   }
}
void CustomerManagerUI::HandleUpdateGender(int id)
{
   Gender newGender = ReadGender("Please give a new gender: ");

   if (manager.UpdateGender(id, newGender)) {
      multiOutput.Print("Gender updated.\n");
   }
   else {
      consoleOutput.Print("Customer not found.\n");
      logOutput.Print("Update gender failed: customer not found.\n");
   }
}
void CustomerManagerUI::HandleDeactivateCustomer(int id)
{
   if (!manager.DeactiveCustomer(id))
   {
      consoleOutput.Print("Customer not found.\n");
      logOutput.Print("Update status failed: customer not found.");
   }
   multiOutput.Print("Customer deactivated.\n");
}
void CustomerManagerUI::HandleUpdateMemberLevel(int id)
{
   MemberLevel newMemberLevel = ReadMemberLevel("Please give a new member level (1.Standard / 2.Private / 3.Premium / 4. Corporate): ");

   if (manager.UpdateMemberLevel(id, newMemberLevel)) {
      multiOutput.Print("Member level updated.\n");
   }
   consoleOutput.Print("Customer not found.\n");
   logOutput.Print("Update member level failed: customer not found.\n");
}
void CustomerManagerUI::HandleUpdateEmail(int id)
{
   std::string newEmail = ReadText("Please give a new email: ");

   if (!Validator::IsValidEmail(newEmail)) {
      consoleOutput.Print("Invalid email format.\n");
      logOutput.Print("Invalid email format entered while updating customer information.\n");
   }

   if (manager.UpdateEmail(id, newEmail)) {
      multiOutput.Print("Email updated.\n");
   }
}
void CustomerManagerUI::HandleUpdateAddress(int id)
{
   std::string newAddress = ReadText("Please give a new Address: ");

   if (!Validator::IsValidAddress(newAddress)) {
      consoleOutput.Print("Invalid address format.\n");
      logOutput.Print("Invalid address format entered while updating customer information.\n");
   }

   if (manager.UpdateAddress(id, newAddress)) {
      multiOutput.Print("Address updated.\n");
   }
}

int CustomerManagerUI::ReadUpdateOption()
{
   return ReadInt("What do you want to update?\n"
      "1. First name\n"
      "2. Last name\n"
      "3. Birthday\n"
      "4. Gender\n"
      "5. Status\n"
      "6. Member level\n"
      "7. Email\n"
      "8. Address\n");
}

void CustomerManagerUI :: HandleUpdate()
{
   if (!manager.HasCustomers()) {
      consoleOutput.Print("No customer is available, please add new customer first.\n");
      return;
   }

   int id = ReadInt("Please enter customer id: ");
   if (!manager.CustomerExists(id))
   {
      consoleOutput.Print("customer not found.\n");
      return;
   }

   int option = ReadUpdateOption();
   switch (option)
   {
      case 1: 
      {
         HandleUpdateFirstName(id);
         break;
      }
      case 2:
      {
         HandleUpdateLastName(id);
         break;
      }
      case 3:
      {
         HandleUpdateDateOfBirth(id);
         break;
      }
      case 4:
      {
         HandleUpdateGender(id);
         break;
      }
      case 5:
      {
         HandleDeactivateCustomer(id);
         break;
      }
      case 6:
      {
         HandleUpdateMemberLevel(id);
         break;
      }
      case 7:
      {
         HandleUpdateEmail(id);
         break;
      }
      case 8:
      {
         HandleUpdateAddress(id);
         break;
      }
      default:
      {
         consoleOutput.Print("Invalid choice.");        
         break;
      }
   }
}
void CustomerManagerUI::HandleRemove()
{
   if (!manager.HasCustomers()) {
      consoleOutput.Print("\n");
      consoleOutput.Print("No customer is available, please add new customer first");
      return;
   }

   int id = ReadInt("Please enter customer id: ");

   if (manager.RemoveById(id)) {
      multiOutput.Print("Customer removed.\n");
      return;
   }
   consoleOutput.Print("Customer not found.\n");
   logOutput.Print("Remove failed: customer not found.\n");
}

