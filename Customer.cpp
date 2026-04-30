#include "Action.h"
#include "Date.h"
#include "Customer.h"
#include "CustomerManager.h"
#include<format>
#include<fstream>
#include<sstream>
using namespace std;



Customer::Customer(const int& valId, const string& valFirstName, const string& valLastName, 
                   const Date& valDateOfBirth, const Gender& valGender, const CustomerStatus& valCustomerStatus, 
                   const MemberLevel& valMemberLevel, const string& valEmail, const string& valAddress) :
                   id{ valId }, firstName {valFirstName}, lastName{ valLastName }, dateOfBirth{ valDateOfBirth }, 
                   gender{ valGender }, customerStatus{ valCustomerStatus }, memberLevel{ valMemberLevel }, 
                   email{ valEmail }, address{ valAddress } {};

const int& Customer::GetId()const
{
   return id;
}

const string& Customer::GetFirstName() const
{
   return firstName;
}
const string& Customer::GetLastName() const
{
   return lastName;
}
const Date& Customer::GetDateOfBirth() const
{
   return dateOfBirth;
}
const Gender& Customer::GetGender() const
{
   return gender;
}
const CustomerStatus& Customer::GetCustomerStatus()const
{
   return customerStatus;
}
const MemberLevel& Customer::GetMemberLevel()const
{
   return memberLevel;
}
const string& Customer::GetEmail()const
{
   return email;
}
const string& Customer::GetAddress()const
{
   return address;
}


void Customer::SetId(int valId)
{
   id = valId;
}

void Customer::SetFirstName(const std::string& valFirstName)
{
   firstName = valFirstName;
}

void Customer::SetLastName(const std::string& valLastName)
{
   lastName = valLastName;
}

void Customer::SetDateOfBirth(const Date& valDateOfBirth)
{
   dateOfBirth = valDateOfBirth;
}

void Customer::SetGender(Gender valGender)
{
   gender = valGender;
}

void Customer::SetCustomerStatus(CustomerStatus valCustomerStatus)
{
   customerStatus = valCustomerStatus;
}

void Customer::SetMemberLevel(MemberLevel valMemberLevel)
{
   memberLevel = valMemberLevel;
}

void Customer::SetEmail(const std::string& valEmail)
{
   email = valEmail;
}

void Customer::SetAddress(const std::string& valAddress)
{
   address = valAddress;
}

void Customer::Print()const
{
   cout << GetId() << " " 
        << GetFirstName() << " " 
        << GetLastName() << " " 
        << GetDateOfBirth().DateToString() << " "
        << GenderToString(GetGender()) << " " 
        << StatusToString(GetCustomerStatus()) << " " 
        << LevelToString(GetMemberLevel()) << " "
        << GetEmail() << " " 
        << GetAddress() << " " << endl;
}

std::string Customer::CustomerToString() const
{

   return std::format("{},{},{},{},{},{},{},{},{}\n",
      std::to_string(id), firstName, lastName, dateOfBirth.DateToString(), 
      GenderToString(gender), StatusToString(customerStatus), 
      LevelToString(memberLevel), email, address);
}

Customer Customer::StringToCustomer(const string& line)
{
   std::stringstream ss(line);
   string part;
  
   Customer c;

   std::getline(ss, part, ',');
   c.SetId(std::stoi(part));

   std::getline(ss, part, ',');
   c.SetFirstName(part);

   std::getline(ss, part, ',');
   c.SetLastName(part);

   std::getline(ss, part, ',');
   c.SetDateOfBirth(Date::StringToDate(part));

   std::getline(ss, part, ',');
   c.SetGender(StringToGender(part));

   std::getline(ss, part, ',');
   c.SetCustomerStatus(StringToStatus(part));

   std::getline(ss, part, ',');
   c.SetMemberLevel(StringToLevel(part));

   std::getline(ss, part, ',');
   c.SetEmail(part);

   std::getline(ss, part, ',');
   c.SetAddress(part);

   return c;
}

