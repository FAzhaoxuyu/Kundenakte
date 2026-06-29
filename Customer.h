#pragma once

#include<string>
#include<vector>
#include<iostream>

#include "Date.h"
#include "CustomerTypes.h"
#include "Contact.h"
#include "ContactMethod.h"



class Customer
{
private:
   int id;
   std::string firstName;
   std::string lastName;
   Date dateOfBirth;
   customerTypes::Gender gender;

   customerTypes::CustomerStatus customerStatus = customerTypes::CustomerStatus::Active;
   customerTypes::MemberLevel memberLevel = customerTypes::MemberLevel::Standard;
   Contact contact;
   Address address;
   ContactType preferredContact = ContactType::None;

 
  
public:
   Customer () = default;
   Customer (const int& valId, const std::string& valFirstName, const std::string& valLastName, const Date& valDateOfBirth, const customerTypes::Gender& valGender, const Contact& valContact, const Address& valAddress);
   const int& GetId ()const;
   const std::string& GetFirstName () const;
   const std::string& GetLastName () const;
   const Date& GetDateOfBirth () const;
   const customerTypes::Gender& GetGender () const;
   const customerTypes::CustomerStatus GetCustomerStatus () const;
   const customerTypes::MemberLevel GetMemberLevel () const;
   std::string GetAddress() const;
   ContactType GetPreferredContact() const;

   void SetFirstName (const std::string& valFirstName);
   void SetLastName (const std::string& valLastName);
   void SetDateOfBirth (const Date& valDateOfBirth);
   void SetGender (customerTypes::Gender valGender);
   void SetCustomerStatus (customerTypes::CustomerStatus valCustomerStatus);
   void SetMemberLevel (customerTypes::MemberLevel valMemberLevel);
   void SetEmail (const std::string& valEmail);
   void SetAddress(const Address& newAddress);
   bool SetPreferredContact(ContactType type);
   void SetContactInfo(ContactType type, const std::string& value);

   void Print () const;

   std::string CustomerToString () const;
   static Customer StringToCustomer (const std::string& line);
   

   


};

