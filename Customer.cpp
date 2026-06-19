#include "Action.h"
#include "Date.h"
#include "Customer.h"
#include "CustomerManager.h"
#include "ContactMethod.h"
#include "Contact.h"
#include<format>
#include<fstream>
#include<sstream>
using namespace std;



Customer::Customer(const int& valId, const string& valFirstName, const string& valLastName,
   const Date& valDateOfBirth, const customerTypes::Gender& valGender, const Contact valContact) :
   id{ valId }, firstName{ valFirstName }, lastName{ valLastName }, dateOfBirth{ valDateOfBirth },
   gender{ valGender }, contact{ valContact } {
};

const int& Customer::GetId () const
{
   return id;
}

const string& Customer::GetFirstName () const
{
   return firstName;
}
const string& Customer::GetLastName () const
{
   return lastName;
}
const Date& Customer::GetDateOfBirth () const
{
   return dateOfBirth;
}
const customerTypes::Gender& Customer::GetGender () const
{
   return gender;
}
const customerTypes::CustomerStatus Customer::GetCustomerStatus () const
{
   return customerStatus;
}

const customerTypes::MemberLevel Customer::GetMemberLevel () const
{
   return memberLevel;
}

//const std::string& Customer::GetEmail () const
//{
//   for (ContactInfo info : contact.GetContactInfos(ContactType::Email)){
//      if (info.type == ContactType::Email){
//         return info.value;
//      }
//      return "";
//   }
//}

const std::string& Customer::GetAddress () const
{
   for (const ContactInfo& info : contact.GetContactInfos(ContactType::Post)) {
      if (info.type == ContactType::Post) {
         return info.value;
      }
   }
   static const std::string empty = "";    //static to avoid Dangling
   return empty;
}

void Customer::SetFirstName (const std::string& valFirstName)
{
   firstName = valFirstName;
}

void Customer::SetLastName (const std::string& valLastName)
{
   lastName = valLastName;
}

void Customer::SetDateOfBirth (const Date& valDateOfBirth)
{
   dateOfBirth = valDateOfBirth;
}

void Customer::SetGender (customerTypes::Gender valGender)
{
   gender = valGender;
}

void Customer::SetCustomerStatus (customerTypes::CustomerStatus valCustomerStatus)
{
   customerStatus = valCustomerStatus;
}

void Customer::SetMemberLevel (customerTypes::MemberLevel valMemberLevel)
{
   memberLevel = valMemberLevel;
}

void Customer::SetEmail (const std::string& valEmail)
{
   contact.SetContactInfo(ContactType::Email,valEmail);
}

void Customer::SetAddress (const Address& valAddress)
{
   contact.SetAddress(valAddress);
}

void Customer::Print () const
{
   cout << GetId() << " " 
        << GetFirstName () << " " 
        << GetLastName () << " " 
        << GetDateOfBirth ().DateToString () << " "
        << customerTypes::GenderToString (GetGender()) << " "
        << customerTypes::StatusToString (GetCustomerStatus()) << " "
        << LevelToString (GetMemberLevel()) << " "
        << contact.EmailsToString() << " " 
        << GetAddress () << " " << endl;
}

std::string Customer::CustomerToString () const
{

   return std::format ("{},{},{},{},{},{},{},{},{}\n",
      std::to_string (id), firstName, lastName, dateOfBirth.DateToString (), 
      customerTypes::GenderToString (gender), customerTypes::StatusToString (customerStatus),
      customerTypes::LevelToString (memberLevel), contact.EmailsToString(), address.ToString());
}

Customer Customer::StringToCustomer (const string& line)
{
   std::stringstream ss (line);
   string part;

   std::getline (ss, part, ',');
   int id = std::stoi (part);

   std::getline (ss, part, ',');
   string parsedFirstName = part;

   std::getline (ss, part, ',');
   string parsedLastName = part;

   std::getline(ss, part, ',');
   Date parsedDateOfBirth = Date::StringToDate (part);

   std::getline (ss, part, ',');
   customerTypes::Gender parsedGender = customerTypes::StringToGender (part);

   std::getline (ss, part, ',');
   customerTypes::CustomerStatus parsedCustomerStatus = customerTypes::StringToStatus (part);

   std::getline (ss, part, ',');
   customerTypes::MemberLevel parsedMemberLevel = customerTypes::StringToLevel (part);

   std::getline (ss, part, ',');
   string parsedEmail = part;

   std::getline(ss, part, ',');
   string parsedStreetAndHouseNr = part;

   std::getline(ss, part, ',');
   string parsedPostCode = part;

   std::getline(ss, part, ',');
   string parsedCity = part;

   std::getline(ss, part, ',');
   string parsedCountry = part;

   Contact parsedContact;
   parsedContact.SetContactInfo(ContactType::Email, parsedEmail);

   Customer customer (id, parsedFirstName, parsedLastName, parsedDateOfBirth, parsedGender, parsedContact);

   customer.SetCustomerStatus (parsedCustomerStatus);
   customer.SetMemberLevel (parsedMemberLevel);
   return customer;
}



