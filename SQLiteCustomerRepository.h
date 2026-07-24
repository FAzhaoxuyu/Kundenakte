#pragma once
#include "CustomerRepository.h"
#include <string>
#include <vector>

class SqliteCustomerRepository : public CustomerRepository
{
public:
   SqliteCustomerRepository (const std::string& databaseFilename);

   std::vector<Customer> Load () const override;
   void Save (const std::vector<Customer>& customers) override;

private:
   std::string databaseFilename;
   void CreateTables () const;
   std::vector<Customer> LoadCustomers() const;

   void LoadCustomers(std::vector<Customer>& customers) const;
   void LoadContactInfos (std::vector<Customer>& customers) const;
   void LoadAddresses (std::vector<Customer>& customers) const;

   void SaveCustomers (const std::vector<Customer>& customers) const ;
   void SaveContactInfos (const std::vector<Customer>& customers) const;
   void SaveAddresses (const std::vector<Customer>& customers) const;
};