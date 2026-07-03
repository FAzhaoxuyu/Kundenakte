#pragma once

#include<string>
namespace ContactData  //ContactMethod
{
   enum class ContactType
   {
      Mobile,
      Landline,
      Email,
      Other,
      //Post,
      None
   };

   enum class ContactStatus
   {
      Valid,
      Invalid
   };

   struct ContactEntry //ContactInfo
   {
   public:
      ContactType type = ContactType::None;
      std::string value = " ";
      ContactStatus status = ContactStatus::Valid;
      bool preferred = false;
   };

   ContactType StringToContactTypes (std::string type);
   std::string ContactTypeToString (ContactType type);
   std::string ContactStatusToString (ContactStatus status);
   ContactStatus StringToContactStatus (std::string status);
}


