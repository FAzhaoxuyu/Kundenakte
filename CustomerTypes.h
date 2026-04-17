#pragma once
#include<string>


enum class Gender
{
   Male,
   Female,
   Diverse
};

enum class CustomerStatus
{
   Active,
   Inactive
};

enum class MemberLevel
{
   Standard,
   Private,
   Premium,
   Corporate
};

std::string ToString(Gender gender);
std::string ToString(CustomerStatus customerStatus);
std::string ToString(MemberLevel memberLevel);
