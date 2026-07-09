#pragma once
#include<string>
#include<vector>

#include "ContactData.h"

class Contact
{
public:
   const std::vector<std::string> GetEmails () const;
   std::string GetPreferredEmail () const;
   void AddInfo (ContactData::ContactType type, const std::string& value);
   const std::vector<ContactData::ContactEntry>& GetContactInfos (ContactData::ContactType type) const;

   void SetContactInfo (ContactData::ContactType type, const std::string& value);
   bool SetPreferredContact (ContactData::ContactType type);
   bool HasContact (ContactData::ContactType type, const std::string& value) const;
   bool IsValid (ContactData::ContactType type) const;
   std::string EmailsToString () const;
   void ClearPreferredContact ();
   const std::vector<ContactData::ContactEntry>& GetAllContactEntries() const;
   std::string ContactInfosToString() const;

private:
   std::vector<ContactData::ContactEntry> contactEntries;
};

