#include "Address.h"

#include <sstream>

Address::Address () {}

AddressType Address::GetType () const
{
   return type;
}

std::string Address::GetStreet () const
{
   return street;
}

std::string Address::GetHouseNr () const
{
   return houseNr;
}

std::string Address::GetPostCode () const
{
   return postCode;
}

std::string Address::GetCity () const
{
   return city;
}

std::string Address::GetCountry  () const
{
   return country;
}

void Address::SetType (AddressType type)
{
   this->type = type;
}

void Address::SetStreet (const std::string& street)
{
   this->street = street;
}

void Address::SetHouseNr (const std::string& houseNr)
{
   this->houseNr = houseNr;
}

void Address::SetPostCode (const std::string& postCode)
{
   this->postCode = postCode;
}

void Address::SetCity (const std::string& city)
{
   this->city = city;
}

void Address::SetCountry (const std::string& country)
{
   this->country = country;
}

std::string Address::ToString () const
{
   std::stringstream ss;

   ss << static_cast<int>(type) << ";"
      << street << ";"
      << houseNr << ";"
      << postCode << ";"
      << city << ";"
      << country;

   return ss.str();
}

Address Address::StringToAddress (const std::string& text)
{
   Address address;

   std::stringstream ss (text);
   std::string part;

   std::getline (ss, part, ';');
   address.SetType(static_cast<AddressType>(std::stoi(part)));

   std::getline (ss, part, ';');
   address.SetStreet(part);

   std::getline (ss, part, ';');
   address.SetHouseNr(part);

   std::getline (ss, part, ';');
   address.SetPostCode(part);

   std::getline (ss, part, ';');
   address.SetCity(part);

   std::getline (ss, part, ';');
   address.SetCountry(part);

   return address;
}