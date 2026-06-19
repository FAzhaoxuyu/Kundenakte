#pragma once
#include<string>
#include<vector>

#include "ContactMethod.h"

class Contact
{
public:
   const std::vector<std::string>& GetEmails() const;
   std::string GetPreferredEmail() const;
   void AddInfo(ContactType type, const std::string& value, bool preferred = false);
   const std::vector<ContactInfo>& GetContactInfos(ContactType type) const;
   void SetAddress(const Address& valAddress);
   void SetContactInfo(ContactType type, const std::string& value);
   std::string EmailsToString() const;

   Address address;
private:
   std::vector<ContactInfo> contactInfos;
};

