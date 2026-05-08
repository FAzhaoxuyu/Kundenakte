#include "CustomerRepository.h"
#include "CustomerManager.h"

#include<fstream>
#include<sstream>
using namespace std;

string Serialize(const vector<Customer>& customers)
{
   string result;
   for (const Customer& customer : customers)
   {
      result += customer.CustomerToString();
   }
   return result;
}
std::vector<Customer> DeSerialize(const string& text)
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

std::vector<Customer> FileCustomerRepository::Load() const 
{
   std::vector<Customer> customers;

   std::ifstream is(filename);
   if (!is)
   {
      std::cerr << "Can't open the file:" << filename << std::endl;
     
      return {};
   }

   try
   {
      std::stringstream buffer;
      buffer << is.rdbuf();
      std::string content = buffer.str();
      customers = DeSerialize(content);

      std::cout << "Loaded customers: " << customers.size() << "\n\n";
      return customers;
   }
   catch (const std::exception& ex)
   {
      std::cerr << "Invalid file content: " << ex.what() << std::endl;
      logger.Print(string("Invalid content: ") + ex.what());
      return {};
   }

}
void FileCustomerRepository::Save(const std::vector<Customer>& customers)
{
   std::ofstream os(filename);
   os << Serialize(customers);
};