#pragma once
#include "CustomerRepository.h"
#include <string>
#include <vector>

class SQLiteCustomerRepository : public CustomerRepository
{
public:
   SQLiteCustomerRepository(const std::string& filename, LogOutput& logger) : filename(filename), logOutput(logger) {};

   std::vector<Customer> Load() const override;
   void Save(const std::vector<Customer>& customers) override;
private:
   std::string filename;
   LogOutput& logOutput;

   std::string GetCustomerFilename() const;
   std::string GetContactFilename() const;
   std::string GetAddressFilename() const;

   std::vector<Customer> LoadCustomers() const;
   void LoadContactInfos(std::vector<Customer>& customers) const;
   void LoadAddresses(std::vector<Customer>& customers) const;

   void SaveCustomers(const std::vector<Customer>& customers) const;
   void SaveContactInfos(const std::vector<Customer>& customers) const;
   void SaveAddresses(const std::vector<Customer>& customers) const;
};