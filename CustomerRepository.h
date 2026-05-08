#pragma once
#include<vector>
#include "Customer.h"
#include"OutputFactory.h"

//class CustomerRepository 
//{
//public:
//   static std::string Serialize(const std::vector<Customer>& customers);
//   static std::vector<Customer> DeSerialize(const std::string& line);
//
//   std::vector<Customer> LoadFromFile(const std::string& filename) const;
//   static void SaveToFile(const std::string& filename, const std::vector<Customer>& customers);
//private:
//   
//};
static std::string Serialize(const std::vector<Customer>& customers);
static std::vector<Customer> DeSerialize(const std::string& line);

class CustomerRepository
{
public:
   virtual std::vector<Customer> Load() const = 0;
   virtual void Save(const std::vector<Customer>& customers) = 0;
private:
   
};

class FileCustomerRepository : public CustomerRepository
{
public:
   FileCustomerRepository(const std::string& filename, Logger& logger) : filename(filename), logger(logger) {};

   std::vector<Customer> Load() const override;
   void Save(const std::vector<Customer>& customers) override;
private:
   std::string filename;
   Logger& logger;
};

class DatabaseCustomerRepository : public CustomerRepository
{
public:
   std::vector<Customer> Load() const override;
   void Save(const std::vector<Customer>& customers) override;
private:
   std::string Database;
};