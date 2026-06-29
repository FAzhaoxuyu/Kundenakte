#pragma once

#include<string>

enum class ContactType
{
   Mobile,
   Landline,
   Email,
   Other,
   Post,
   None
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
   ContactStatus status = ContactStatus::Valid;
   bool preferred;
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
ContactType StringToContactType(std::string type);
std::string ContactTypeToString(ContactType type);

