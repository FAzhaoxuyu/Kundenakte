#include "Customer.h"
#include "CustomerManager.h"
#include "CustomerManagerUI.h"
#include "CustomerRepository.h"

#include<algorithm>
#include<sstream>
#include<fstream>
#include<filesystem>

using namespace std;

const std::vector<Customer>& CustomerManager::GetCustomers () const
{
   return customers;
}

bool CustomerManager::HasCustomers () const
{
   return !customers.empty();
}

std::vector<Customer>::iterator CustomerManager::FindCustomerById (int searchid)
{
   auto it = find_if (customers.begin(), customers.end(), [searchid] (const Customer& customer) {return customer.GetId() == searchid; });
   return it;
}

int CustomerManager::GenerateCustomerId ()
{
   if (customers.size() == 0) {
      return 1;
   }
   else {
      auto it = std::max_element (customers.begin(), customers.end(), [](const Customer& a, const Customer& b) {return a.GetId() < b.GetId();});
      return it->GetId() + 1;
   }
}

void CustomerManager::Add (Customer& newCustomer)
{
   customers.push_back(newCustomer);
   repository.Save(customers);
}

bool CustomerManager::UpdateFirstName (int id, const std::string& newFirstName)
{
   std::vector<Customer>::iterator it = FindCustomerById (id);
   if (it == customers.end()) return false;
   it->SetFirstName(newFirstName);
   repository.Save(customers);
   return true;
}
bool CustomerManager::UpdateLastName (int id, const std::string& newLastName)
{
   std::vector<Customer>::iterator it = FindCustomerById(id);
   if (it == customers.end()) return false;
   it->SetLastName(newLastName);
   repository.Save(customers);
   return true;
}
bool CustomerManager::UpdateDateOfBirth (int id, const Date& newDateOfBirth)
{
   std::vector<Customer>::iterator it = FindCustomerById(id);
   if (it == customers.end()) return false;
   it->SetDateOfBirth(newDateOfBirth);
   repository.Save(customers);
   return true;
}
bool CustomerManager::UpdateGender (int id, customerTypes::Gender newGender)
{
   std::vector<Customer>::iterator it = FindCustomerById(id);
   if (it == customers.end()) return false;
   it->SetGender(newGender);
   repository.Save(customers);
   return true;
}
bool CustomerManager::UpdateCustomerStatus (int id, customerTypes::CustomerStatus newStatus) {
   std::vector<Customer>::iterator it = FindCustomerById(id);
   if (it == customers.end()) return false;
   it->SetCustomerStatus(newStatus);
   repository.Save(customers);
   return true;
}
bool CustomerManager::UpdateMemberLevel (int id, customerTypes::MemberLevel newLevel)
{
   std::vector<Customer>::iterator it = FindCustomerById(id);
   if (it == customers.end()) return false;
   it->SetMemberLevel(newLevel);
   repository.Save(customers);
   return true;
}
bool CustomerManager::UpdateEmail (int id, const std::string& newEmail)
{
   std::vector<Customer>::iterator it = FindCustomerById(id);
   if (it == customers.end()) return false;
   it->SetEmail(newEmail);
   repository.Save(customers);
   return true;
}
bool CustomerManager::UpdateAddress (int id, const Address& newAddress)
{
   std::vector<Customer>::iterator it = FindCustomerById(id);
   if (it == customers.end()) return false;
   it->SetAddress(newAddress);
   repository.Save(customers);
   return true;
}

bool CustomerManager::UpdateStatus (int id, customerTypes::CustomerStatus newStatus)
{
   auto it = FindCustomerById(id);
   if (it == customers.end()) return false;

   it->SetCustomerStatus(newStatus);
   repository.Save(customers);
   return true;
}

bool CustomerManager::CustomerExists (int id) const
{
   auto it = find_if(customers.begin(), customers.end(), 
      [id](const Customer& customer) 
      {return customer.GetId() == id; });
   return it != customers.end();
}

bool CustomerManager::RemoveById (int id)
{
   auto it = FindCustomerById(id);
   if (it == customers.end()) {
      return false;
   }
   else {
      customers.erase(it);
      repository.Save(customers);
      return true;
   }
}

bool CustomerManager::DeactiveCustomer (int id)
{
   auto it = find_if(customers.begin(), 
      customers.end(), 
      [id](const Customer& customer) 
      {return customer.GetId() == id;});

   if (it != customers.end()) {
      it->SetCustomerStatus(customerTypes::CustomerStatus::Inactive);
      repository.Save(customers);
      return true;
   }
   return false;
}


// Learning example for Strategy Pattern.
// Sorting may later be moved to database queries using ORDER BY.
void CustomerManager :: SortCustomers(const CustomerSortStrategy& strategy)
{
   strategy.Sort(customers);
}
