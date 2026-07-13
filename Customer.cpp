#include "Action.h"
#include "Date.h"
#include "Customer.h"
#include "CustomerManager.h"
#include "ContactData.h"
#include "Contact.h"
#include "StringUtils.h"
#include "Address.h"
#include<format>
#include<fstream>
#include<sstream>
using namespace std;



Customer::Customer (
   const int& valId,
   const string& valFirstName,
   const string& valLastName,
   const Date& valDateOfBirth,
   const customerTypes::Gender& valGender,
   const customerTypes::CustomerStatus& valStatus,
   const customerTypes::MemberLevel& valLevel) :
   id (valId),
   firstName (valFirstName),
   lastName (valLastName),
   dateOfBirth (valDateOfBirth),
   gender (valGender),
   customerStatus (valStatus),
   memberLevel (valLevel) {};

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

const std::vector<Address>& Customer::GetAddresses() const
{
   return addresses;
}

const Contact& Customer::GetContact() const
{
   return contact;
}

ContactData::ContactType Customer::GetPreferredContact () const
{
   return preferredContact;
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
   contact.SetContactInfo(ContactData::ContactType::Email,valEmail);
}

void Customer::SetAddress (const Address& newAddress)
{
   addresses.push_back(newAddress);
}

void Customer::SetContact(const Contact& newContact)
{
   contact = newContact;
}

bool Customer::SetPreferredContact (ContactData::ContactType type)
{
   // Post is not in contact, it is in address
   if (contact.SetPreferredContact(type)) {
      preferredContact = type;
      return true;
   }
   return false;
}

void Customer::SetContactInfo (ContactData::ContactType type, const std::string& value)
{
   contact.SetContactInfo(type, value);
}

void Customer::AddAddress(const Address& address)
{
   addresses.push_back(address);
}

void Customer::AddContactInfo(ContactData::ContactType type, const std::string& value)
{
   contact.AddInfo(type, value);
}

void Customer::Print () const
{
   cout << GetId() << " "
      << GetFirstName() << " "
      << GetLastName() << " "
      << GetDateOfBirth().DateToString() << " "
      << customerTypes::GenderToString(GetGender()) << " "
      << customerTypes::StatusToString(GetCustomerStatus()) << " "
      << customerTypes::LevelToString(GetMemberLevel()) << endl;

   cout << "Contacts: " << contact.ContactInfosToString() << endl;

   cout << "Addresses: ";
   for (const Address& address : addresses) {
      cout << address.ToString() << " | ";
   }
   cout << endl;
}

std::string Customer::CustomerToString () const
{
   return std::format ("{},{},{},{},{},{},{}\n",
      std::to_string (id),
      firstName,
      lastName,
      dateOfBirth.DateToString(), 
      customerTypes::GenderToString (gender),
      customerTypes::StatusToString (customerStatus),
      customerTypes::LevelToString (memberLevel));
}

std::string Customer::CustomerDetailsToString () const
{
   string result;
   result += "Customer: \n";
   result += to_string (id) + " "
      + firstName + " "
      + lastName + " "
      + dateOfBirth.DateToString() + " "
      + customerTypes::GenderToString (gender) + " "
      + customerTypes::StatusToString(customerStatus) + " "
      + customerTypes::LevelToString(memberLevel) + "\n\n"; 

   result += "Contacts:\n";
   result += contact.ContactInfosToString() + "\n\n";

   result += "Addresses:\n";
   for (const Address& address : addresses) {
      result += address.ToString() + "\n";
   }

   result += "\nPreferred contact: ";
   result += ContactData::ContactTypeToString (preferredContact);
   result += "\n";

   return result;
}

Customer Customer::StringToCustomer (const string& line)
{
   std::vector<string> parts = StringUtils::SplitLine (line, ',');

   int id = std::stoi (parts[0]);
   string firstName = parts[1];
   string lastName = parts[2];
   Date dateOfBirth = Date::StringToDate (parts[3]);
   customerTypes::Gender gender = customerTypes::StringToGender (parts[4]);
   customerTypes::CustomerStatus status = customerTypes::StringToStatus (parts[5]);
   customerTypes::MemberLevel memberLevel = customerTypes::StringToLevel (parts[6]);

   //Contact contact;
   //contact.AddInfo(ContactData::ContactType::Email, parts[7]);

   //Address address = Address::StringToAddress (parts[8]);
   //address.SetPostCode(parts[9]);
   //address.SetCity(parts[10]);
   //address.SetCountry(parts[11]);
   
   Customer customer (id, firstName, lastName, dateOfBirth, gender, status, memberLevel);
   //customer.SetCustomerStatus(status);
   //customer.SetMemberLevel(memberLevel);

 /*  if (parts.size() > 12 && !parts[12].empty()){
      customer.SetPreferredContact(ContactData::StringToContactTypes(parts[12]));
   }*/

   return customer;
}



