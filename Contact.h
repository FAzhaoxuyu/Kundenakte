#pragma once
#include<string>
#include<vector>

#include "ContactMethod.h"

class Contact
{
public:
   const std::vector<std::string> GetEmails() const;
   std::string GetPreferredEmail() const;
   void AddInfo(ContactType type, const std::string& value);
   const std::vector<ContactInfo>& GetContactInfos(ContactType type) const;

   void SetContactInfo(ContactType type, const std::string& value);
   bool SetPreferredContact(PreferredContactType type);
   bool HasContact(PreferredContactType type) const;
   std::string EmailsToString() const;


private:
   std::vector<ContactInfo> contactInfos;
};

