#pragma once

#include<string>
#include<vector>
#include<iostream>

#include "Date.h"
#include "CustomerTypes.h"
#include "Action.h"


class Customer
{
private:
   int id;
   std::string firstName;
   std::string lastName;
   Date dateOfBirth;
   Gender gender;
   CustomerStatus customerStatus = CustomerStatus :: Active;
   MemberLevel memberLevel = MemberLevel ::Standard;
   std::string email;
   std::string address;
public:
   Customer() = default;
   Customer(const int& valId, const std::string& valFirstName, const std::string& valLastName, const Date& valDateOfBirth, const Gender& valGender, const CustomerStatus& valCustomerStatus, const MemberLevel& valMemberLevel, const std::string& valEmail, const std::string& valAddress);
   const int& GetId()const;
   const std::string& GetFirstName()const;
   const std::string& GetLastName()const;
   const Date& GetDateOfBirth()const;
   const Gender& GetGender()const;
   const CustomerStatus& GetCustomerStatus()const;
   const MemberLevel& GetMemberLevel()const;
   const std::string& GetEmail()const;
   const std::string& GetAdress()const;

   void SetId(int valId);
   void SetFirstName(const std::string& valFirstName);
   void SetLastName(const std::string& valLastName);
   void SetDateOfBirth(const Date& valDateOfBirth);
   void SetGender(Gender valGender);
   void SetCustomerStatus(CustomerStatus valCustomerStatus);
   void SetMemberLevel(MemberLevel valMemberLevel);
   void SetEmail(const std::string& valEmail);
   void SetAddress(const std::string& valAddress);

   void Print()const;

   


};

