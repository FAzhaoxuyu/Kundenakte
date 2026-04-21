#include "Action.h"
#include "Customer.h"
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
        << GetDateOfBirth().ToString() << " "
        << ToString(GetGender()) << " " 
        << ToString(GetCustomerStatus()) << " " 
        << ToString(GetMemberLevel()) << " "
        << GetEmail() << " " 
        << GetAddress() << " " << endl;
}