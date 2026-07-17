#include "SQLiteCustomerRepository.h"
using namespace std;

std::vector<Customer> SQLiteCustomerRepository::Load() const
{
   vector<Customer> customers = LoadCustomers();
   LoadContactInfos(customers);
   LoadAddresses(customers);
   return customers;
}

void SQLiteCustomerRepository::Save(const vector<Customer>& customers)
{
   SaveCustomers(customers);
   SaveContactInfos(customers);
   SaveAddresses(customers);
}

std::vector<Customer> SQLiteCustomerRepository::LoadCustomers() const     // continue from here 
{
   vector<Customer> customers;

   ifstream is(GetCustomerFilename());
   if (!is) {
      cerr << "Can't open the file:" << filename << std::endl;
      return {};
   }

   try {
      stringstream buffer;
      buffer << is.rdbuf();
      string content = buffer.str();
      cout << "File content:\n\n" << content << "\n";
      customers = DeSerialize(content);

      cout << "Loaded customers: " << customers.size() << "\n\n";
      return customers;
   }
   catch (const std::exception& ex) {
      cerr << "Invalid file content: " << ex.what() << std::endl;
      logOutput.Print(string("Invalid content: ") + ex.what());
      return {};
   }
}

string SQLiteCustomerRepository::GetCustomerFilename() const
{
   return "customers.csv";
}
string SQLiteCustomerRepository::GetContactFilename() const
{
   return "contacts.csv";
}
string SQLiteCustomerRepository::GetAddressFilename() const
{
   return "addresses.csv";
}

void SQLiteCustomerRepository::LoadContactInfos(vector<Customer>& customers) const
{
   ifstream file(GetContactFilename());
   if (!file.is_open()) return;

   string line;
   std::getline(file, line);

   while (getline(file, line)) {
      stringstream ss(line);

      string idText;
      string typeText;
      string value;
      string statusText;
      string preferredText;

      getline(ss, idText, ',');
      getline(ss, typeText, ',');
      getline(ss, value, ',');

      getline(ss, statusText, ',');
      getline(ss, preferredText, ',');

      int customerId = stoi(idText);
      ContactData::ContactType type = ContactData::StringToContactTypes(typeText);

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

void SQLiteCustomerRepository::LoadAddresses(vector<Customer>& customers) const
{
   ifstream file(GetAddressFilename());

   if (!file) {
      cerr << "Can't open the file: " << GetAddressFilename() << endl;
      return;
   }

   string line;
   getline(file, line);   //skip header
   while (getline(file, line)) {
      stringstream ss(line);
      string customerIdText;
      string typeText;
      string street;
      string houseNr;
      string postCode;
      string city;
      string country;

      getline(ss, customerIdText, ',');
      getline(ss, typeText, ',');
      getline(ss, street, ',');
      getline(ss, houseNr, ',');
      getline(ss, postCode, ',');
      getline(ss, city, ',');
      getline(ss, country, ',');

      int customerId = std::stoi(customerIdText);
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

void SQLiteCustomerRepository::SaveCustomers(const std::vector<Customer>& customers) const
{
   ofstream file(GetCustomerFilename());

   if (!file.is_open()) {
      cerr << "Can't open the file: " << GetCustomerFilename() << endl;          //Customer::CustomerToString() need to change
      return;
   }


   file << Serialize(customers);
}
void SQLiteCustomerRepository::SaveContactInfos(const std::vector<Customer>& customers) const
{
   ofstream file(GetContactFilename());
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
void SQLiteCustomerRepository::SaveAddresses(const std::vector<Customer>& customers) const
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