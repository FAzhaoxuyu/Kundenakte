#include "CustomerRepository.h"
#include "CustomerManager.h"
#include "ContactData.h"
#include "Address.h"
#include <filesystem>
#include<fstream>
#include<sstream>
using namespace std;

string Serialize (const vector<Customer>& customers)
{
   string result;
   for (const Customer& customer : customers) {
      result += customer.CustomerToString ();
   }
   return result;
}
std::vector<Customer> DeSerialize (const string& text)
{
   vector<Customer> result;
   string line;
   stringstream ss (text);      

   while (std::getline (ss, line)) {
      Customer c = Customer::StringToCustomer (line);
      result.push_back(c);
   }
   return result;
}

std::vector<Customer> FileCustomerRepository :: Load () const
{
   vector<Customer> customers = LoadCustomers ();
   LoadContactInfos (customers);
   LoadAddresses (customers);
   return customers;
}

void FileCustomerRepository :: Save (const vector<Customer>& customers)
{
   SaveCustomers (customers);
   SaveContactInfos (customers);
   SaveAddresses (customers);
}

std::vector<Customer> FileCustomerRepository :: LoadCustomers () const     // continue from here 
{
   vector<Customer> customers;

   ifstream is (GetCustomerFilename ());
   if (!is) {
      cerr << "Can't open the file:" << filename << std::endl; 
      return {};
   }

   try {
      stringstream buffer;
      buffer << is.rdbuf();
      string content = buffer.str();
      cout << "File content:\n\n" << content << "\n";
      customers = DeSerialize (content);

      cout << "Loaded customers: " << customers.size() << "\n\n";
      return customers;
   }
   catch (const std::exception& ex) {
      cerr << "Invalid file content: " << ex.what() << std::endl;
      logOutput.Print(string ("Invalid content: ") + ex.what());
      return {};
   }
}

string FileCustomerRepository::GetCustomerFilename () const
{
   return "customers.csv";
}
string FileCustomerRepository::GetContactFilename () const
{
   return "contacts.csv";
}
string FileCustomerRepository::GetAddressFilename () const
{
   return "addresses.csv";
}

void FileCustomerRepository::LoadContactInfos (vector<Customer>& customers) const
{
   ifstream file (GetContactFilename ());
   if (!file.is_open()) return;

   string line;
   std::getline(file, line);

   while (getline (file, line)) {
      stringstream ss (line);

      string idText;
      string typeText;
      string value;
      string statusText;
      string preferredText;

      getline (ss, idText, ',');
      getline (ss, typeText, ',');
      getline (ss, value, ',');

      getline(ss, statusText, ',');
      getline(ss, preferredText, ',');

      int customerId = stoi (idText);
      ContactData::ContactType type = ContactData::StringToContactTypes (typeText);

      bool preferred = (preferredText == "1");

      for (Customer& customer : customers) {
         if (customer.GetId() == customerId) {
            customer.AddContactInfo(type, value);
            if (preferred) {
               customer.SetPreferredContact(type);
            }
         }
      }
   }
}

void FileCustomerRepository::LoadAddresses (vector<Customer>& customers) const
{
   ifstream file (GetAddressFilename ());

   if (!file) {
      cerr << "Can't open the file: " << GetAddressFilename () << endl;
      return;
   }

   string line;
   getline(file, line);   //skip header
   while (getline (file, line)) {
      stringstream ss(line);
      string customerIdText;
      string typeText;
      string street;
      string houseNr;
      string postCode;
      string city;
      string country;

      getline (ss, customerIdText, ',');
      getline (ss, typeText, ',');
      getline (ss, street, ',');
      getline(ss, houseNr, ',');
      getline (ss, postCode, ',');
      getline (ss, city, ',');
      getline (ss, country, ',');

      int customerId = std::stoi (customerIdText);
      Address address;

    
      address.SetType(StringToAddressType(typeText));
      address.SetStreet(street);
      address.SetHouseNr(houseNr);
      address.SetPostCode(postCode);
      address.SetCity(city);
      address.SetCountry(country);

      for (Customer& customer : customers) {
         if (customer.GetId() == customerId) {
            customer.AddAddress(address);
            break;
         }
      }
   }
}

void FileCustomerRepository::SaveCustomers (const std::vector<Customer>& customers) const
{
   ofstream file (GetCustomerFilename());

   if (!file.is_open()) {
      cerr << "Can't open the file: " << GetCustomerFilename() << endl;          //Customer::CustomerToString() need to change
      return;
   }


   file << Serialize(customers);
}
void FileCustomerRepository::SaveContactInfos (const std::vector<Customer>& customers) const
{
   ofstream file (GetContactFilename());
   if (!file.is_open()) {
      cerr << "Can't open the file: " << GetContactFilename() << endl;
      return;
   }

   for (const Customer& customer : customers) {
      for (const ContactData::ContactEntry& info : customer.GetContact().GetAllContactEntries()) {
         file << customer.GetId() << "," << ContactData::ContactTypeToString(info.type) << "," << info.value << ","
              << ContactData::ContactStatusToString(info.status) << "," << info.preferred << "\n";
      }
   }
}
void FileCustomerRepository::SaveAddresses (const std::vector<Customer>& customers) const
{
   ofstream file(GetAddressFilename());
   if (!file.is_open()) {
      cerr << "Can't open the file: " << GetAddressFilename() << endl;
      return;
   }
   for (const Customer& customer : customers) {
      for (const Address& address : customer.GetAddresses()) {
         file << customer.GetId() << ","
            << AddressTypeToString(address.GetType()) << ","
            << address.GetStreet() << ","
            << address.GetHouseNr() << ","
            << address.GetPostCode() << ","
            << address.GetCity() << ","
            << address.GetCountry() << "\n";
      }
   }
}