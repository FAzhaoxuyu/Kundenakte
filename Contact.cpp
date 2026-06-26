#include "Contact.h"
#include "ContactMethod.h"

#include<iostream>

const std::vector<std::string> Contact::GetEmails() const
{
   std::vector<std::string> emails;

   for (auto& info : contactInfos) {
      if (info.type == ContactType::Email) {
         emails.push_back(info.value);
      }
   }
   return emails;
}

//std::string Contact::GetPreferredEmail() const
//{
//   for (const auto& info : contactInfos)
//   {
//      if (info.type == ContactType::Email && info.preferred && info.status == ContactStatus::Valid){
//         return info.value;
//      }
//   }
//   return "";
//}


void Contact::AddInfo (ContactType type, const std::string& value)
{
   contactInfos.emplace_back (type, value, ContactStatus::Valid);
}

const std::vector<ContactInfo>& Contact::GetContactInfos (ContactType type) const
{
   return contactInfos;
}

void Contact::SetContactInfo (ContactType type, const std::string& value)
{
   for (ContactInfo& info : contactInfos) {
      if (info.type == type) {
         info.value = value;
         return;
      }
   }
   contactInfos.push_back ({ type, value, ContactStatus::Valid });
}

bool Contact::HasContact(PreferredContactType type) const
{
   for (const ContactInfo& info : contactInfos)
   {
      switch (type)
      {
      case PreferredContactType::Mobile:
         if (info.type == ContactType::Mobile)
            return true;
         break;

      case PreferredContactType::Landline:
         if (info.type == ContactType::Landline)
            return true;
         break;

      case PreferredContactType::Email:
         if (info.type == ContactType::Email)
            return true;
         break;

      case PreferredContactType::Other:
         if (info.type == ContactType::Other)
            return true;
         break;

      default:
         break;
      }
   }

   return false;
}

std::string Contact::EmailsToString() const
{
   std::string result;

   for (const std::string& email : GetEmails())
   {
      if (!result.empty())
      {
         result += ";";
      }

      result += email;
   }

   return result;
}