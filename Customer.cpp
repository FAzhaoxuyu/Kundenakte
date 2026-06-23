#include "Action.h"
#include "Date.h"
#include "Customer.h"
#include "CustomerManager.h"
#include "ContactMethod.h"
#include "Contact.h"
#include "StringUtils.h"
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

std::string Customer::GetAddress() const
{
   const std::vector<ContactInfo>& posts = contact.GetContactInfos(ContactType::Post);
   string result;
   for (const ContactInfo& info : posts) {
      result += info.value + " ";
   }
   return result;
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

bool Customer::SetPreferredContact(ContactType type)
{
   return contact.SetPreferredContact(type);
}

void Customer::SetContactInfo(ContactType type, const std::string& value)
{
   contact.SetContactInfo(type, value);
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
      customerTypes::LevelToString (memberLevel), contact.EmailsToString(), GetAddress());
}

Customer Customer::StringToCustomer (const string& line)
{
   std::vector<string> parts = StringUtils::SplitLine(line, ',');

   int id = std::stoi(parts[0]);
   string firstName = parts[1];
   string lastName = parts[2];
   Date dateOfBirth = Date::StringToDate(parts[3]);
   customerTypes::Gender gender = customerTypes::StringToGender(parts[4]);
   customerTypes::CustomerStatus status = customerTypes::StringToStatus(parts[5]);
   customerTypes::MemberLevel memberLevel = customerTypes::StringToLevel(parts[6]);

   Contact contact;
   contact.AddInfo(ContactType::Email, parts[7]);

   Address address = Address::StringToAddress(parts[8]);
   address.postCode = parts[9];
   address.city = parts[10];
   address.country = parts[11];
   contact.AddInfo(ContactType::Post, address.ToString());
   
   Customer customer(id, firstName, lastName, dateOfBirth, gender, contact);
   customer.SetCustomerStatus(status);
   customer.SetMemberLevel(memberLevel);

   return customer;
}



