#include "ContactData.h"

#include <string>
#include <sstream>
#include "Algorithm"

ContactData::ContactType ContactData::StringToContactTypes (std::string type)
{
   std::transform(type.begin(), type.end(), type.begin(), ::tolower);
   if (type == "none") return ContactData::ContactType::None;
   if (type == "mobile") return ContactData::ContactType::Mobile;
   if (type == "landline") return ContactData::ContactType::Landline;
   if (type == "email") return ContactData::ContactType::Email;
   if (type == "other") return ContactData::ContactType::Other;

   throw std::invalid_argument (type);
}



std::string ContactData::ContactTypeToString (ContactData::ContactType type)
{
   switch (type)
   {
   case ContactData::ContactType::None: return "None";
   case ContactData::ContactType::Mobile: return "Mobile";
   case ContactData::ContactType::Landline: return "Landline";
   case ContactData::ContactType::Email: return "Email";
   case ContactData::ContactType::Other: return "Other";
   default: return "Unknown";
   }
}

std::string ContactData:: ContactStatusToString (ContactStatus status)
{
   if (status == ContactStatus::Valid) return "Valid";
   if (status == ContactStatus::Invalid) return "Invalid";
   return "Invalid";
}

ContactData::ContactStatus ContactData::StringToContactStatus (std::string status)
{
   std::transform (status.begin(), status.end(), status.begin(), ::tolower);

   if (status == "valid") return ContactStatus::Valid;
   if (status == "invalid") return ContactStatus::Invalid;

   throw std::invalid_argument (status);
}