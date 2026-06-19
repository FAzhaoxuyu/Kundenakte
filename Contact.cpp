#include "Contact.h"
#include "ContactMethod.h"

const std::vector<std::string>& Contact::GetEmails() const
{
   std::vector<std::string> emails;

   for (auto& info : contactInfos) {
      if (info.type == ContactType::Email) {
         emails.push_back(info.value);
      }
   }
   return emails;
}

std::string Contact::GetPreferredEmail() const
{
   for (const auto& info : contactInfos)
   {
      if (info.type == ContactType::Email && info.preferred && info.status == ContactStatus::Valid){
         return info.value;
      }
   }
   return "";
}


void Contact::AddInfo(ContactType type, const std::string& value, bool preferred)
{
   contactInfos.emplace_back(type, value, preferred, ContactStatus::Valid);
}

const std::vector<ContactInfo>& Contact::GetContactInfos(ContactType type) const
{
   return contactInfos;
}

void Contact::SetContactInfo(ContactType type, const std::string& value)
{
   for (ContactInfo& info : contactInfos) {
      if (info.type == type) {
         info.value = value;
         return;
      }
   }
   contactInfos.push_back({ type, value, false, ContactStatus::Valid });
}

void Contact::SetAddress(const Address& valAddress)
{
   address = valAddress;
}



//const std::vector<std::string>& Contact::GetMobileNrs() const
//{
//   return mobileNrs;
//}
//const std::vector<std::string>& Contact::GetTeleNrs() const
//{
//   return teleNrs;
//}

//const ContactTypes Contact::GetPreferredContacts() const
//{
//   return prefer;
//}
//
//void Contact::AddMobileNr(const std::string& newMobileNr)
//{
//   mobileNrs.push_back(newMobileNr);
//}
//
//void Contact::AddTeleNr(const std::string& newTeleNr)
//{
//   teleNrs.push_back(newTeleNr);
//}
//void Contact::AddEmail(const std::string& newEmail)
//{
//   emails.push_back(newEmail);
//}
//void Contact::SetPreffered(ContactTypes type)
//{
//   prefer = type;
//}

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