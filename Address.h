#pragma once
#include <string>

#pragma once
#include <string>

enum class AddressType
{
   Home,
   Work,
   Billing
};

class Address
{
public:
   Address ();

   AddressType GetType () const;
   std::string GetStreet () const;
   std::string GetHouseNr () const;
   std::string GetPostCode () const;
   std::string GetCity () const;
   std::string GetCountry () const;

   void SetType (AddressType type);
   void SetStreet (const std::string& street);
   void SetHouseNr (const std::string& houseNr);
   void SetPostCode (const std::string& postCode);
   void SetCity (const std::string& city);
   void SetCountry (const std::string& country);

   std::string ToString () const;
   static Address StringToAddress (const std::string& text);

private:
   AddressType type = AddressType::Home;
   std::string street;
   std::string houseNr;
   std::string postCode;
   std::string city;
   std::string country;
};