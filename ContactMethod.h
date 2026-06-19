#pragma once

#include<string>

enum class ContactType
{
   Mobile,
   Landline,
   Email,
   Post,
   Other
};

enum class ContactStatus
{
   Valid,
   Invalid
};

struct ContactInfo
{
public:
   ContactType type;
   std::string value;
   bool preferred = false;
   ContactStatus status = ContactStatus::Valid;
};

struct Address
{
   std::string street;
   std::string HouseNr;
   std::string postCode;
   std::string city;
   std::string country;

   std::string ToString() const;
   static Address StringToAddress(const std::string& text);
};

ContactType StringToContactTypes(std::string type);

