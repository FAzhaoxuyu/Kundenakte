#include "Contact.h"
#include "ContactData.h"
using namespace std;
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
   if (HasContact(type, value)) {
      return;
   }
   ContactData::ContactEntry entry;
   entry.type = type;
   entry.value = value;
   entry.status = ContactData::ContactStatus::Valid;
   entry.preferred = false;

   contactEntries.push_back(entry);
}

void Contact::AddContactInfo(const ContactData::ContactEntry& entry)
{
   contactEntries.push_back(entry);
}

const std::vector<ContactData::ContactEntry>& Contact::GetContactInfos (ContactData::ContactType type) const
{
   return contactEntries;
}

const std::vector<ContactData::ContactEntry>& Contact::GetContactEntries() const
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
   if (!IsValid(type)) {
      return false;
   }

   for (auto& info : contactEntries) {
      info.preferred = (info.type == type);
   }

   return true;
}

bool Contact::HasContact (ContactData::ContactType type, const string& value) const
{
   for (const auto& info : contactEntries) {
      if (info.type == type && info.value == value) {
         return true;
      }
   }
   return false;
}

bool Contact::IsValid (ContactData::ContactType type) const
{
   for (const auto& info : contactEntries) {
      if (info.type == type && info.status == ContactData::ContactStatus::Valid) {
         return true;
      }
   }
   return false;
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
      result += "\n";
   }

   return result;
}