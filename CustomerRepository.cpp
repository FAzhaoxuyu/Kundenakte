#include "CustomerRepository.h"
#include "CustomerManager.h"
#include<fstream>
#include<sstream>
using namespace std;

string CustomerRepository::Serialize(const vector<Customer>& customers)
{
   string result;
   for (const Customer& customer : customers)
   {
      result += customer.CustomerToString();
   }
   return result;
}
std::vector<Customer> CustomerRepository::DeSerialize(const string& text)
{
   std::vector<Customer> result;
   string line;
   stringstream ss(text);

   while (std::getline(ss, line))
   {
      Customer c = Customer::StringToCustomer(line);
      result.push_back(c);
   }
   return result;
}

std::vector<Customer> CustomerRepository::LoadFromFile(const string& filename) const 
{
   std::vector<Customer> customers;

   std::ifstream is(filename);
   if (!is)
   {
      std::cerr << "Can't open the file." << filename << std::endl;
      return {};
   }

   std::stringstream buffer;
   buffer << is.rdbuf();
   std::string content = buffer.str();
   customers = DeSerialize(content);
   return customers;
}
void CustomerRepository::SaveToFile(const string& filename, const std::vector<Customer>& customers)
{
   std::ofstream os(filename);
   os << Serialize(customers);
};