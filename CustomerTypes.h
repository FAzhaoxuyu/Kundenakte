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

std::string GenderToString(Gender gender);
std::string StatusToString(CustomerStatus customerStatus);
std::string LevelToString(MemberLevel memberLevel);

Gender StringToGender(const std::string& text);
CustomerStatus StringToStatus(const std::string& text);
MemberLevel StringToLevel(const std::string& text);