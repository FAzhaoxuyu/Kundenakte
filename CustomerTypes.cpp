#include "CustomerTypes.h"
#include<string>
using namespace std;

string ToString(Gender gender)
{
   switch (gender)
   {
   case Gender::Male: return "Male";
   case Gender::Female: return "Female";
   case Gender::Diverse: return "Diverse";
   }
}
string ToString(CustomerStatus customerStatus)
{
   switch (customerStatus)
   {
   case CustomerStatus::Active: return "Active";
   case CustomerStatus::Inactive: return "Inactive";
   }
}
string ToString(MemberLevel memberLevel)
{
   switch (memberLevel)
   {
   case MemberLevel::Standard: return "Standard";
   case MemberLevel::Private: return "Private";
   case MemberLevel::Premium: return "Premium";
   case MemberLevel::Corporate: return "Corporate";
   }
}
