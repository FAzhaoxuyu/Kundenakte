#include "Date.h"
#include "Action.h"
#include "Customer.h"
#include "CustomerManager.h"
#include "CustomerManagerUI.h"
#include "CustomerRepository.h"
#include "OutputFactory.h"
#include "Validator.h"
#include "CreateCustomerStep.h"
#include "StepNavigator.h"
#include <iostream>

using namespace std;

//void CustomerManagerUI::ShowMenu ()
//{
//   consoleOutput.Print("===== Customer Management =====\n");
//   consoleOutput.Print("1: Add\n");
//   consoleOutput.Print("2: Update\n");
//   consoleOutput.Print("3: Remove\n");
//   consoleOutput.Print("4: Show\n");
//   consoleOutput.Print("5: Help\n");
//   consoleOutput.Print("6: Exit\n");
//   consoleOutput.Print("===============================\n");
//}
void CustomerManagerUI::ShowMainMenu()
{
   consoleOutput.Print("===== Customer Management =====\n");
   consoleOutput.Print("1: Add Customer\n");
   consoleOutput.Print("2: Select Customer\n");
   consoleOutput.Print("3: Show All Customers\n");
   consoleOutput.Print("4: Help\n");
   consoleOutput.Print("5: Exit\n");
   consoleOutput.Print("===============================\n");
}

string CustomerManagerUI::ReadText (const string& question)
{
   while (true){
      consoleOutput.Print(question);
      string input;
      getline(cin, input);
      if (!input.empty()){
         return input;
      }
      consoleOutput.Print("Invalid input, please enter agian.\n");
   }
}

int CustomerManagerUI::ReadDay ()
{
   while (true){
      int day = ReadInt("Day: ");
      if (day >= 1 && day <= 31){
         return day;
      }
      consoleOutput.Print("Invalid day.\n");
   }
}

int CustomerManagerUI::ReadMonth ()
{
   while (true){
      int month = ReadInt("Month: ");
      if (month >= 1 && month <= 12){
         return month;
      }
      consoleOutput.Print("Invalid month.\n");
   }
}

int CustomerManagerUI::ReadYear ()
{
   while (true){
      int year = ReadInt("Year: ");
      if (year >= 1900 && year <= 2100){
         return year;
      }
      consoleOutput.Print("Invalid year.\n");
   }
}

int CustomerManagerUI::ReadInt (const string& question)
{
   while (true){
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




customerTypes::MemberLevel CustomerManagerUI::ReadMemberLevel (const string& question)
{
   while (true){
      int choice = ReadInt(question);

      switch (choice)
      {
      case 1: return customerTypes::MemberLevel::Standard;
      case 2: return customerTypes::MemberLevel::Private;
      case 3: return customerTypes::MemberLevel::Premium;
      case 4: return customerTypes::MemberLevel::Corporate;
      default:
         consoleOutput.Print("Invalid member level, please enter again.\n");
      }
   }
}

void CustomerManagerUI::Show()
{
   if (!manager.HasCustomers()) {
      consoleOutput.Print("\n");
      consoleOutput.Print("No customer is available, please add new customer first.\n");
      return;
   }

   for (const Customer& customer : manager.GetCustomers()) {
      consoleOutput.Print(customer.CustomerToString() + "\n");
   }
}

void CustomerManagerUI::ShowCustomerMenu()
{
   consoleOutput.Print("\n===== Customer Menu =====\n");
   consoleOutput.Print("Current customer ID: " + std::to_string(selectedCustomerID) + "\n");
   consoleOutput.Print("1: Update\n");
   consoleOutput.Print("2: Remove\n");
   consoleOutput.Print("3: Show customer\n");
   consoleOutput.Print("4: Set preferred contact method\n");
   consoleOutput.Print("5: Back\n");
   consoleOutput.Print("=========================\n");
}

void CustomerManagerUI::HandleUpdateSelectedCustomer()
{
   while (true) {
      int option = ReadUpdateOption();

      switch (option)
      {
      case 1:
         HandleUpdateFirstName();
         break;

      case 2:
         HandleUpdateLastName();
         break;

      case 3:
         HandleUpdateDateOfBirth();
         break;

      case 4:
         HandleUpdateGender();
         break;

      case 5:
         HandleDeactivateCustomer();
         break;

      case 6:
         HandleUpdateMemberLevel();
         break;

      case 7:
         HandleUpdateEmail();
         break;

      case 8:
         HandleUpdateAddress();
         break;

      default:
         consoleOutput.Print("Invalid choice.\n");
         break;
      }
   } 
}


void CustomerManagerUI::HandleShowSelectedCustomer()
{
   for (const Customer& customer : manager.GetCustomers())
   {
      if (customer.GetId() == selectedCustomerID)
      {
         consoleOutput.Print(customer.CustomerToString() + "\n");
         return;
      }
   }

   consoleOutput.Print("Customer not found.\n");
   selectedCustomerID = -1;
}

void CustomerManagerUI::HandleSetPreferredContact()
{
   ContactType type = ReadPreferredContactMethod();
   bool success = manager.SetPreferredContact(selectedCustomerID, type);
   if (success) {
      multiOutput.Print("Preffered contact method updated.\n");
   }
   else {
      consoleOutput.Print("failed to update preferred contact methord.\n");
   }
}

void CustomerManagerUI::HandleCustomerMenu()
{
   ShowCustomerMenu();
   int option = ReadInt("Please choose an option: ");
   switch (option)
   {
   case 1:
      HandleUpdateSelectedCustomer();
      break;

   case 2:
      HandleRemoveSelectedCustomer();
      break;

   case 3:
      HandleShowSelectedCustomer();
      break;

   case 4:
      HandleSetPreferredContact();
      break;

   case 5:
      selectedCustomerID = -1;
      break;

   default:
      consoleOutput.Print("Invalid choice.\n");
      break;
   }
}

void CustomerManagerUI::Run ()
{
   while (true){
      if (selectedCustomerID == -1) {
         ShowMainMenu();

         Action option = ReadOption("Please choose an option: ");

         switch (option)
         {
         case Action::Add:
         {
            HandleAdd();
            break;
         }
         case Action::Select:
         {
            HandleSelect();
            break;
         }

         //case Action::Update:
         //{
         //   HandleUpdate();
         //   break;
         //}
         //case Action::Remove:
         //{
         //   HandleRemove();
         //   break;
         //}
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
            return;
         }

         }
      }

      else {
         HandleCustomerMenu();
      }

   }
   
}


Action CustomerManagerUI::ReadOption (const string& question)
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
         //case 2: return Action::Update;
         //case 3: return Action::Remove;
         case 2: return Action::Select;
         case 3: return Action::Show;
         case 4: return Action::Help;
         case 5: return Action::Exit;
         default : consoleOutput.Print("Invalid input, please choose an option again.");
         }
      }
      catch (const exception& ex)
      {
         errorLogger.Print(std::string("Invalid input: ") + ex.what() + "\n");
         consoleOutput.Print("Invalid input, please enter again.\n");
      }
   }
}

string CustomerManagerUI::ReadValidatedFirstName ()
{
   while (true){
      string firstName = ReadText("Please enter a new first name: ");
      if (!Validator::IsValidSingleName(firstName)){
         consoleOutput.Print("Invalid firstNname, please enter again.\n");
         continue;
      }
      return firstName;
   }
}

std::string CustomerManagerUI::ReadValidatedLastName ()
{
   while (true){
     string  lastName = ReadText("Please enter a new last name: ");
      if (!Validator::IsValidSingleName(lastName)){
         consoleOutput.Print("Invalid  last name, please enter again.\n");
         continue;
      }
      return lastName;
   }
}
Date CustomerManagerUI::ReadDate (const std::string& question)
{
   while (true){
      consoleOutput.Print(question + "\n");
      int day = ReadDay();
      int month = ReadMonth();
      int year = ReadYear();

      return Date(day, month, year); 
   }
}

Date CustomerManagerUI::ReadValidatedDate ()
{
   while (true) {
      Date date = ReadDate("Please enter date of birth: ");
      if (Validator::IsValidDate(date.GetDay(), date.GetMonth(), date.GetYear())) {
         return date;
      }

      consoleOutput.Print("Invalid input, please enter again.\n");
   }
}

customerTypes::Gender CustomerManagerUI::ReadGender (const string& question)
{
   while (true) {
      int choice = ReadInt("Please choose gender: 1.Male / 2.Female /3.Diverse: ");
      switch (choice)
      {
      case 1: return customerTypes::Gender::Male;
      case 2: return customerTypes::Gender::Female;
      case 3: return customerTypes::Gender::Diverse;
      default: consoleOutput.Print("Invalid input, please choose again.\n");
         break;
      }
   }
}


string CustomerManagerUI::ReadValidatedEmail ()
{
   while (true) {
     string email = ReadText("Please enter email: ");
      if (!Validator::IsValidEmail(email)){
         consoleOutput.Print("Invalid email.\n");
         continue;
      }
      return email;
   }
}
string CustomerManagerUI::ReadValidatedAddress ()
{
   while (true){
      string address = ReadText("Please enter address: ");
      if (!Validator::IsValidAddress(address)){
         consoleOutput.Print("Invalid address.\n");
         continue;
      }
      return address;
   }
}

std::vector<std::string> CustomerManagerUI::ReadPhoneNrs()
{
   std::vector<string> phoneNrs;
   while (true) {
      string input = ReadText("Phone Number (press Enter to finish): ");
      if (input.empty()) {
         break;
      }
      else if (Validator::IsValidMobileNr(input)) {
         phoneNrs.push_back(input);
      }
      else {
         consoleOutput.Print("Invalid phone number.");
      }
   }
   return phoneNrs;
}

std::vector<std::string> CustomerManagerUI::ReadMobileNrs()
{
   return ReadPhoneNrs();
}

std::vector<std::string> CustomerManagerUI::ReadTeleNrs()
{
   return ReadPhoneNrs();
}

Contact CustomerManagerUI::ReadContact()
{
   Contact contact;
   while (true) {
      ContactType type = ReadContactType();
      std::string value = ReadText("Enter contact type: ");
      if (Validator::IsValidContact(type, value)) {
         contact.AddInfo(type, value);
      }
      else{
         consoleOutput.Print("Invalid contact value.\n");
      }
      
   }
   return contact;

}

ContactType CustomerManagerUI::ReadContactType()
{ 
   while (true) {
      try {
         return StringToContactTypes(ReadText("Contact type (Mobile /Landline /Email /Post /Other): "));
      }
      catch (const std::invalid_argument& e) {
         consoleOutput.Print("Invalid contact type. Please try again.\n");
      }
   } 
}

Contact CustomerManagerUI::ReadValidContact ()
{
   Contact contact;
   while (true)
   {
      ContactType type = ReadContactType();
      std::string value = ReadText("Enter contact information: ");

      contact.AddInfo(type, value);

      std::string answer = ReadText("Add another contact? (y/n): ");

      if (answer == "n" || answer == "N")
         break;
   }

   return contact;
}

ContactType CustomerManagerUI::ReadPreferredContactMethod ()
{
   while (true) {
      try {
         ContactType choice = StringToContactTypes(ReadText("Preferred contact method (Mobile/Landline/Email/Post/Other): "));
         return choice;
      }
      catch (const std::invalid_argument& e) {
         consoleOutput.Print(std::string("Invalid contact type: ") + e.what());
      }
   }
  
}

Customer CustomerManagerUI::CreateCustomer ()
{
   StepNavigator<CreateCustomerStep> navi({
   CreateCustomerStep::FirstName,
   CreateCustomerStep::LastName,
   CreateCustomerStep::DateOfBirth,
   CreateCustomerStep::Gender,
   CreateCustomerStep::MemberLevel,
   CreateCustomerStep::Contact,
   CreateCustomerStep::Address
   });

   int id = manager.GenerateCustomerId ();
   string firstName = ReadValidatedFirstName ();
   string lastName = ReadValidatedLastName ();
   Date dateOfBirth = ReadValidatedDate (); 
   customerTypes::Gender gender = ReadGender("Gender (1.Male / 2.Female / 3.Diverse): ");
   customerTypes::CustomerStatus customerStatus = customerTypes::CustomerStatus::Active;
   customerTypes::MemberLevel memberLevel = ReadMemberLevel ("Member level (1.Standard / 2.Private / 3.Premium / 4. Corporate): ");

   string addressText = ReadValidatedAddress ();
   Address address = Address::StringToAddress(addressText);

   Contact contact = ReadValidContact();
  

   Customer newCustomer = Customer (id, firstName, lastName, dateOfBirth, gender, contact);

   newCustomer.SetCustomerStatus(customerStatus);
   newCustomer.SetMemberLevel(memberLevel);
 
   contact.AddInfo(ContactType::Post, address.ToString());

   return newCustomer;
}


void CustomerManagerUI::Help ()
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
void CustomerManagerUI::Exit ()
{
   //std::unique_ptr<Output> output = std::make_unique<ConsoleOutput>();

   consoleOutput.Print("Exit called\n");
   consoleOutput.Print("Program closed.");
}

void CustomerManagerUI::HandleAdd ()
{
   Customer customer = CreateCustomer ();
   manager.Add(customer);
   multiOutput.Print("A new customer added.\n");
}

void CustomerManagerUI::HandleSelect ()
{
   int id = ReadInt("Please enter customer id: ");

   if (!manager.CustomerExists(id)){
      consoleOutput.Print("Customer not found.\n");
      return;
   }
   selectedCustomerID = id;
   consoleOutput.Print("Customer selected.\n");
}

bool CustomerManagerUI::HasSelectedCustomer() const
{
   return selectedCustomerID != -1;
}

void CustomerManagerUI::HandleUpdateFirstName ()
{
   std::string newFirstName = ReadValidatedFirstName ();

   if (!HasSelectedCustomer())
   {
      consoleOutput.Print("No customer selected.\n");
      return;
   }

   if (manager.UpdateFirstName(selectedCustomerID, newFirstName)) {
      multiOutput.Print("First name updated.\n");
   }
   else {
      consoleOutput.Print("Customer not found.\n");
      errorLogger.Print("Update first name failed: customer not found.\n");
   }
}
void CustomerManagerUI::HandleUpdateLastName ()
{
   std::string newLastName = ReadValidatedLastName();

   if (!HasSelectedCustomer())
   {
      consoleOutput.Print("No customer selected.\n");
      return;
   }
  
   if (manager.UpdateLastName(selectedCustomerID, newLastName)) {
      multiOutput.Print("Last name updated.\n");
   }
   else {
      consoleOutput.Print("Customer not found.\n");
      errorLogger.Print("Update last name failed: customer not found.\n");
   }
}
void CustomerManagerUI::HandleUpdateDateOfBirth ()
{
   Date newDateOfBirth = ReadValidatedDate ();

   if (!HasSelectedCustomer())
   {
      consoleOutput.Print("No customer selected.\n");
      return;
   }

   if (manager.UpdateDateOfBirth(selectedCustomerID, newDateOfBirth)) {
      multiOutput.Print("Date of birth updated.\n");
   }
   else {
      consoleOutput.Print("Customer not found.\n");
      errorLogger.Print("Update birthday failed: customer not found.\n");
   }
}
void CustomerManagerUI::HandleUpdateGender ()
{
   customerTypes::Gender newGender = ReadGender("Please give a new gender: ");

   if (!HasSelectedCustomer())
   {
      consoleOutput.Print("No customer selected.\n");
      return;
   }

   if (manager.UpdateGender(selectedCustomerID, newGender)) {
      multiOutput.Print("Gender updated.\n");
   }
   else {
      consoleOutput.Print("Customer not found.\n");
      errorLogger.Print("Update gender failed: customer not found.\n");
   }
}
void CustomerManagerUI::HandleDeactivateCustomer ()
{
   if (!HasSelectedCustomer())
   {
      consoleOutput.Print("No customer selected.\n");
      return;
   }
   if (!manager.DeactiveCustomer(selectedCustomerID)){
      consoleOutput.Print("Customer not found.\n");
      errorLogger.Print("Update status failed: customer not found.");
   }
   else {
      multiOutput.Print("Customer deactivated.\n");
   } 
}
void CustomerManagerUI::HandleUpdateMemberLevel()
{
   customerTypes::MemberLevel newMemberLevel = ReadMemberLevel("Please give a new member level (1.Standard / 2.Private / 3.Premium / 4. Corporate): ");

   if (!HasSelectedCustomer())
   {
      consoleOutput.Print("No customer selected.\n");
      return;
   }

   if (manager.UpdateMemberLevel(selectedCustomerID, newMemberLevel)) {
      multiOutput.Print("Member level updated.\n");
   }
   else {
      consoleOutput.Print("Customer not found.\n");
      errorLogger.Print("Update member level failed: customer not found.\n");
   }
}
void CustomerManagerUI::HandleUpdateEmail ()
{
   std::string newEmail = ReadValidatedEmail();
   if (!HasSelectedCustomer())
   {
      consoleOutput.Print("No customer selected.\n");
      return;
   }

   if (manager.UpdateEmail(selectedCustomerID, newEmail)){
      multiOutput.Print("Email updated.\n");
   }
   else {
      consoleOutput.Print("Invalid email format.\n");
      logOutput.Print("Invalid email format entered while updating customer information.\n");
   }
}
void CustomerManagerUI::HandleUpdateAddress ()
{
   std::string newAddress = ReadValidatedAddress();

   if (!HasSelectedCustomer())
   {
      consoleOutput.Print("No customer selected.\n");
      return;
   }

   if (manager.UpdateAddress(selectedCustomerID, Address::StringToAddress(newAddress))) {
      multiOutput.Print("Address updated.\n");
   }
   else {
      consoleOutput.Print("Invalid address format.\n");
      logOutput.Print("Invalid address format entered while updating customer information.\n");
   }
}

int CustomerManagerUI::ReadUpdateOption ()
{
   return ReadInt("What do you want to update?\n"
      "1. First name\n"
      "2. Last name\n"
      "3. Birthday\n"
      "4. Gender\n"
      "5. Status\n"
      "6. Member level\n"
      "7. Email\n"
      "8. Address\n"
      "9. Back\n");
}


void CustomerManagerUI::HandleRemoveSelectedCustomer()
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
   errorLogger.Print("Remove failed: customer not found.\n");
}

