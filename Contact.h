#pragma once
#include<string>
#include<vector>

#include "ContactMethod.h"

class Contact
{
public:
   const std::vector<std::string> GetEmails () const;
   std::string GetPreferredEmail () const;
   void AddInfo (ContactType type, const std::string& value);
   const std::vector<ContactInfo>& GetContactInfos (ContactType type) const;

   void SetContactInfo (ContactType type, const std::string& value);
   bool SetPreferredContact (ContactType type);
   /*bool HasContact (ContactType type) const;*/
   std::string EmailsToString () const;
   void ClearPreferredContact();

private:
   std::vector<ContactInfo> contactInfos;
};

