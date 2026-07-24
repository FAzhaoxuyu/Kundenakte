#include "SQLiteCustomerRepository.h"
#include "external/SQLiteCpp/header_only_src/SqliteWrapper.hpp"
#include "Contact.h"
#include "ContactData.h"

using namespace std;

SqliteCustomerRepository::SqliteCustomerRepository (const std::string& databaseFilename) : databaseFilename (databaseFilename) {CreateTables();};

vector<Customer> SqliteCustomerRepository::Load () const
{
   vector<Customer> customers = LoadCustomers();
   LoadContactInfos(customers);
   LoadAddresses(customers);
   return customers;
}

void SqliteCustomerRepository::Save (const vector<Customer>& customers)
{
   SaveCustomers(customers);
   SaveContactInfos(customers);
   SaveAddresses(customers);
}

void SqliteCustomerRepository::CreateTables () const
{
   Sqlite::SqliteConnection connection (databaseFilename.c_str());

   Sqlite::SqliteStatement createCustomersTable (                                           //customer table
      connection,
      "CREATE TABLE IF NOT EXISTIS customers ("
      "CustomerId INTEGER PRIMARY KEY,"
      "FirstName TEXT NOT NULL,"
      "LastName TEXT NOT NULL,"
      "DateOfBirth TEXT NOT NULL,"
      "Gender TEXT NOT NULL,"
      "Status TEXT NOT NULL,"
      "Level TEXT NOT NULL,"
      ");"
   );
   createCustomersTable.execute();

   Sqlite::SqliteStatement createContactInfosTable(                                      //address table
      connection,
      "CREATE TABLE IF NOT EXISTS contactInfos ("
      "contactInfoId INTEGER PRIMARY KEY,"
      "CustomerId INTEGER NOT NULL,"
      "Type TEXT NOT NULL,"
      "Value TEXT NOT NULL,"
      "Status TEXT NOT NULL,"
      "IsPreferred TEXT NOT NULL,"
      "FOREIGN KEY(CustomerId) REFERENCES Customers(CustomerId)"
      ");" 
   );
   createContactInfosTable.execute();

   Sqlite::SqliteStatement createAddressesTable(
      connection,
      "CREATE TABLE IF NOT EXISTS Addresses ("
      "AddressId INTEGER PRIMARY KEY,"
      "CustomerId INTEGER NOT NULL,"
      "Type TEXT NOT NULL,"
      "Street TEXT NOT NULL,"
      "HouseNr TEXT NOT NULL,"
      "PostCode TEXT NOT NULL,"
      "City TEXT NOT NULL,"
      "Country TEXT NOT NULL,"
      "FOREIGN KEY(CustomerId) REFERENCES Customers(CustomerId)"
      ");"
   );
   createAddressesTable.execute();
}

void SqliteCustomerRepository::SaveCustomers (const std::vector<Customer>& customers) const
{
   Sqlite::SqliteConnection connection(databaseFilename.c_str());

   for (const Customer& customer : customers) {
      int customerId = customer.GetId();
      string firstName = customer.GetFirstName();
      string lastName = customer.GetLastName();
      string dateOfBirth = customer.GetDateOfBirth().DateToString();
      string gender = customerTypes::GenderToString(customer.GetGender());
      string status = customerTypes::StatusToString(customer.GetCustomerStatus());
      string level = customerTypes::LevelToString(customer.GetMemberLevel());

      string sql = "INSERT INTO Customers (CustomerId, Firstname, LastName, DateOfBirth, Gender, CustomerStatus, MemberLevel) VALUES (?, ?, ?, ?, ?, ?, ?);";
      Sqlite::SqliteStatement statement(connection, sql.c_str());
      statement.bind(1, customerId);
      statement.bind(2, firstName);
      statement.bind(3, lastName);
      statement.bind(4, dateOfBirth);
      statement.bind(5, gender);
      statement.bind(6, status);
      statement.bind(7, level);
      
      statement.execute();
   }
}

void SqliteCustomerRepository::SaveContactInfos(const std::vector<Customer>& customers) const
{
   Sqlite::SqliteConnection connection(databaseFilename.c_str());
   
   for (const Customer& customer : customers) {
      for (const ContactData::ContactEntry& entry : customer.GetContact().GetContactEntries()) {
         ContactData::ContactType type = entry.type;
         const string& value = entry.value;
         ContactData::ContactStatus status = entry.status;
         bool preferred = entry.preferred;
         string preferredText = entry.preferred ? "true": "false";

         string sql = "INSERT INTO ContactInfos (CustomerId, Type, Value, Status, isPreferred) VALUES (?, ?, ?, ?, ?)";

         Sqlite::SqliteStatement statement(connection, sql.c_str());
         statement.bind(1, customer.GetId());
         statement.bind(2, static_cast<int>(type));
         statement.bind(3, value.c_str());
         statement.bind(4, static_cast<int>(status));
         statement.bind(5, preferredText);

         statement.execute();
      }
   }
}

void SqliteCustomerRepository::SaveAddresses (const std::vector<Customer>& customers) const
{
   Sqlite::SqliteConnection connection(databaseFilename.c_str());

   for (const Customer& customer : customers) {
      for (const Address& address : customer.GetAddresses()) {

         string sql = "Insert into Address (CustomerId, Type, Street, HouseNr, PostCode, City, Country) VALUES (?, ?, ?, ?, ?, ?,?)";
         Sqlite::SqliteStatement statement(connection, sql.c_str());

         statement.bind(1, customer.GetId());
         statement.bind(2, static_cast<int>(address.GetType()));
         statement.bind(3, address.GetStreet());
         statement.bind(4, address.GetHouseNr());
         statement.bind(5, address.GetPostCode());
         statement.bind(6, address.GetCity());
         statement.bind(7, address.GetCountry());

         statement.execute();
      }
   }
}

void SqliteCustomerRepository::LoadCustomers(std::vector<Customer>& customers) const
{
   Sqlite::SqliteConnection connection (databaseFilename.c_str());
   string sql = "SELECT CustomerId, Type, Value, Status, isPreferred FROM Customers";
   Sqlite::SqliteStatement statement(connection, sql.c_str());

   while (statement.execute()) {
      Customer customer;
      int id = statement.getInt(0);
      string firstName = statement.getString(1);
      string lastName = statement.getString(2);
      string dateOfBirth = statement.getString(3);
      string gender = statement.getString(4);
      string status = statement.getString(5);
      string level = statement.getString(6);

      customer.SetId(id);
      customer.SetFirstName(firstName);
      customer.SetLastName(lastName);
      customer.SetDateOfBirth(Date::StringToDate(dateOfBirth));
      customer.SetGender(customerTypes::StringToGender(gender));
      customer.SetCustomerStatus(customerTypes::StringToStatus(status));
      customer.SetMemberLevel(customerTypes::StringToLevel(level));

      customers.push_back(customer);
   }
}

void SqliteCustomerRepository::LoadContactInfos (std::vector<Customer>& customers) const
{
   Sqlite::SqliteConnection connection(databaseFilename.c_str());
   string sql = "SELECT CustomerId, Type, Value, Status, isPreferred FROM CotactInfos";
   Sqlite::SqliteStatement statement(connection, sql.c_str());

   while (statement.execute()) {
      int customerId = statement.getInt(0);

      ContactData::ContactEntry contactEntry;
      contactEntry.type = ContactData::StringToContactTypes(statement.getString(1));
      contactEntry.value = statement.getString(2);
      contactEntry.status = ContactData::StringToContactStatus(statement.getString(3));
      contactEntry.preferred = std::string(statement.getString(4)) == "true";

      for (Customer& customer : customers) {
         if (customer.GetId() == customerId) {
            customer.AddContactInfo(contactEntry);
            break;
         }
      }
   }
}

void SqliteCustomerRepository::LoadAddresses (std::vector<Customer>& customers) const
{

}

