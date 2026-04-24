#include "Customer.h"
#include "CustomerManager.h"
#include "CustomerManagerUI.h"
#include<algorithm>
#include<sstream>
#include<fstream>

using namespace std;

const std::vector<Customer>& CustomerManager::GetCustomers() const
{
   return customers;
}

bool CustomerManager::IsEmpty() const
{
   return customers.empty();
}

std::vector<Customer>::iterator CustomerManager::FindCustomerById(int searchid)
{
   auto it = find_if(customers.begin(), customers.end(), [searchid](const Customer& customer) {return customer.GetId() == searchid; });
   return it;
}

int CustomerManager::GenerateCustomerId()
{
   if (customers.size() == 0) {
      return 1;
   }
   else {
      auto it = std::max_element(customers.begin(), customers.end(), [](const Customer& a, const Customer& b) {return a.GetId() < b.GetId();});
      return it->GetId() + 1;
   }
}

const void CustomerManager::Add(Customer& newCustomer)
{
   customers.push_back(newCustomer);
}

bool CustomerManager::UpdateFirstName(int id, const std::string& newFirstName)
{
   std::vector<Customer>::iterator it = FindCustomerById(id);
   if (it == customers.end()) return false;
   it->SetFirstName(newFirstName);
   return true;
}
bool CustomerManager::UpdateLastName(int id, const std::string& newLastName)
{
   std::vector<Customer>::iterator it = FindCustomerById(id);
   if (it == customers.end()) return false;
   it->SetLastName(newLastName);
   return true;
}
bool CustomerManager::UpdateDateOfBirth(int id, const Date& newDateOfBirth)
{
   std::vector<Customer>::iterator it = FindCustomerById(id);
   if (it == customers.end()) return false;
   it->SetDateOfBirth(newDateOfBirth);
   return true;
}
bool CustomerManager::UpdateGender(int id, Gender newGender)
{
   std::vector<Customer>::iterator it = FindCustomerById(id);
   if (it == customers.end()) return false;
   it->SetGender(newGender);
   return true;
}
bool CustomerManager::UpdateCustomerStatus(int id, CustomerStatus newStatus) {
   std::vector<Customer>::iterator it = FindCustomerById(id);
   if (it == customers.end()) return false;
   it->SetCustomerStatus(newStatus);
   return true;
}
bool CustomerManager::UpdateMemberLevel(int id, MemberLevel newLevel)
{
   std::vector<Customer>::iterator it = FindCustomerById(id);
   if (it == customers.end()) return false;
   it->SetMemberLevel(newLevel);
   return true;
}
bool CustomerManager::UpdateEmail(int id, const std::string& newEmail)
{
   std::vector<Customer>::iterator it = FindCustomerById(id);
   if (it == customers.end()) return false;
   it->SetEmail(newEmail);
   return true;
}
bool CustomerManager::UpdateAddress(int id, const std::string& newAddress)
{
   std::vector<Customer>::iterator it = FindCustomerById(id);
   if (it == customers.end()) return false;
   it->SetAddress(newAddress);
   return true;
}

bool CustomerManager::RemoveById(int id)
{
   auto it = FindCustomerById(id);
   if (it == customers.end()) {
      return false;
   }
   else {
      customers.erase(it);
      return true;
   }
}

string CustomerManager::Serialize() const
{
   string result;
   for (const Customer& customer : customers)
   {
      result += customer.CustomerToString();
   }
   return result;
}
std::vector<Customer> CustomerManager::DeSerialize(const string& text)
{
   std::vector<Customer> result;
   string line;
   stringstream ss (text);
   
   while (std::getline(ss, line))
   {
      Customer c = Customer::StringToCustomer(line);
      result.push_back(c);
   }
   return result;
}

void CustomerManager::SaveToFile(const string& filename) const
{
   std::ofstream os(filename);
   os << Serialize();
}

void CustomerManager::LoadFromFile(const string& filename)
{
   std::ifstream is(filename);
   if (!is)
   {
      std::cerr << "Error: can not open the file '" << filename << "'\n";
   }
   std::stringstream buffer;
   buffer << is.rdbuf();
   std::string fileContent = buffer.str();
   DeSerialize(fileContent);
}