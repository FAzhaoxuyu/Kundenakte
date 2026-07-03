#pragma once
#include<vector>
#include "Customer.h"
#include"OutputFactory.h"

static std::string Serialize (const std::vector<Customer>& customers);
static std::vector<Customer> DeSerialize (const std::string& line);

class CustomerRepository
{
public:
   virtual std::vector<Customer> Load () const = 0;
   virtual void Save (const std::vector<Customer>& customers) = 0;
private:
   
};

class FileCustomerRepository : public CustomerRepository
{
public:
   FileCustomerRepository (const std::string& filename, LogOutput& logger) : filename (filename), logOutput (logger) {};

   std::vector<Customer> Load () const override;
   void Save (const std::vector<Customer>& customers) override;
private:
   std::string filename;
   LogOutput& logOutput;

   std::string GetCustomerFilename () const;
   std::string GetContactFilename () const;
   std::string GetAddressFilename () const;

   std::vector<Customer> LoadCustomers () const;
   void LoadContactInfos (std::vector<Customer>& customers) const;
   void LoadAddresses (std::vector<Customer>& customers) const;

   void SaveCustomers (const std::vector<Customer>& customers) const;
   void SaveContactInfos (const std::vector<Customer>& customers) const;
   void SaveAddresses (const std::vector<Customer>& customers) const;
};

//class DatabaseCustomerRepository : public CustomerRepository
//{
//public:
//   std::vector<Customer> Load () const override;
//   void Save(const std::vector<Customer>& customers) override;
//private:
//   std::string database;
//};