#pragma once
#include<vector>
#include "Customer.h"

class CustomerRepository 
{
public:
   static std::string Serialize(const std::vector<Customer>& customers);
   static std::vector<Customer> DeSerialize(const std::string& line);

   std::vector<Customer> LoadFromFile(const std::string& filename) const;
   static void SaveToFile(const std::string& filename, const std::vector<Customer>& customers);
private:
   
};