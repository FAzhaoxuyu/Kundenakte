
#pragma once

#include<string>
#include<vector>
#include<iostream>

#include "Date.h"
#include "CustomerTypes.h"
#include "Contact.h"
#include "ContactData.h"
#include "Address.h"



class Customer
{
private:
   int id = 0;
   std::string firstName;
   std::string lastName;
   Date dateOfBirth;
   customerTypes::Gender gender;
   customerTypes::CustomerStatus customerStatus = customerTypes::CustomerStatus::Active;
   customerTypes::MemberLevel memberLevel = customerTypes::MemberLevel::Standard;

   Contact contact;
   std::vector<Address> addresses;
   ContactData::ContactType preferredContact = ContactData::ContactType::None;

 
  
public:
   Customer () = default;
   Customer (const int& valId,
      const std::string& valFirstName,
      const std::string& valLastName,
      const Date& valDateOfBirth,
      const customerTypes::Gender& valGender,
      const customerTypes::CustomerStatus& valStatus,
      const customerTypes::MemberLevel& valLevel);

   const int& GetId () const;
   const std::string& GetFirstName () const;
   const std::string& GetLastName () const;
   const Date& GetDateOfBirth () const;
   const customerTypes::Gender& GetGender () const;
   const customerTypes::CustomerStatus GetCustomerStatus () const;
   const customerTypes::MemberLevel GetMemberLevel () const;
   const std::vector<Address>& GetAddresses () const;
   const Contact& GetContact () const;
   ContactData::ContactType GetPreferredContact () const;

   void SetFirstName (const std::string& valFirstName);
   void SetLastName (const std::string& valLastName);
   void SetDateOfBirth (const Date& valDateOfBirth);
   void SetGender (customerTypes::Gender valGender);
   void SetCustomerStatus (customerTypes::CustomerStatus valCustomerStatus);
   void SetMemberLevel (customerTypes::MemberLevel valMemberLevel);
   void SetEmail (const std::string& valEmail);
   void SetAddress (const Address& newAddress);
   void SetContact(const Contact& newContact);
   bool SetPreferredContact (ContactData::ContactType type);
   void SetContactInfo (ContactData::ContactType type, const std::string& value);
   void AddAddress (const Address& address);

   void AddContactInfo(ContactData::ContactType type, const std::string& value);
   void AddContactInfo(const ContactData::ContactEntry& entry);

   void Print () const;

   std::string CustomerToString () const;
   std::string CustomerDetailsToString() const;
   static Customer StringToCustomer (const std::string& line);
   

   


};

