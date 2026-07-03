#include "Contact.h"
#include "ContactData.h"

#include<iostream>

const std::vector<std::string> Contact::GetEmails () const
{
   std::vector<std::string> emails;

   for (auto& info : contactEntries) {
      if (info.type == ContactData::ContactType::Email) {
         emails.push_back(info.value);
      }
   }
   return emails;
}

//std::string Contact::GetPreferredEmail() const
//{
//   for (const auto& info : contactInfos) {
//      if (info.type == ContactType::Email && info.preferred && info.status == ContactStatus::Valid) {
//         return info.value;
//      }
//   }
//   return "";
//}


void Contact::AddInfo (ContactData::ContactType type, const std::string& value)
{
   contactEntries.emplace_back(type, value, ContactData::ContactStatus::Valid);
}

const std::vector<ContactData::ContactEntry>& Contact::GetContactInfos (ContactData::ContactType type) const
{
   return contactEntries;
}

void Contact::SetContactInfo (ContactData::ContactType type, const std::string& value)
{
   for (ContactData::ContactEntry& info : contactEntries) {
      if (info.type == type) {
         info.value = value;
         return;
      }
   }
   contactEntries.push_back({ type, value, ContactData::ContactStatus::Valid });
}

bool Contact::SetPreferredContact (ContactData::ContactType type)
{
   bool found = false;
   for (auto& info : contactEntries) {
      if (info.type == type && info.status == ContactData::ContactStatus::Valid) {
         info.preferred = true;
         found = true;
      }
      else {
         info.preferred = false;
      }
   }
   return found;
}

std::string Contact::EmailsToString () const
{
   std::string result;

   for (const std::string& email : GetEmails ())
   {
      if (!result.empty())
      {
         result += ";";
      }

      result += email;
   }

   return result;
}

void Contact::ClearPreferredContact ()
{
   for (auto& info : contactEntries) {
      info.preferred = false;
   }
}

const std::vector<ContactData::ContactEntry>& Contact::GetAllContactEntries () const
{
   return contactEntries;
}

std::string Contact::ContactInfosToString() const
{
   std::string result;

   for (const ContactData::ContactEntry& info : contactEntries)
   {
      result += ContactData::ContactTypeToString (info.type);
      result += ": ";
      result += info.value;
      result += " | ";
   }

   return result;
}