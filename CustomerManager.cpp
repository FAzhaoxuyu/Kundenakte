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

std::vector<ContactData::ContactEntry>
CustomerManager::GetContactEntries (int customerId)
{
   Customer& customer = FindCustomerById (customerId);
   return customer.GetContact().GetAllContactEntries();
}

bool CustomerManager::HasCustomers () const
{
   return !customers.empty();
}

//std::vector<Customer>::iterator CustomerManager::FindCustomerById (int searchid)
//{
//   auto it = find_if (customers.begin(), customers.end(), [searchid] (const Customer& customer) {return customer.GetId() == searchid; });
//   return it;
//}

Customer& CustomerManager::FindCustomerById (int searchid)
{
   auto it = find_if(customers.begin(), customers.end(), [searchid](const Customer& customer) { return customer.GetId() == searchid; });
   if (it != customers.end()) return *it;
   throw runtime_error("Customer not found.");
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
   Customer& customer = FindCustomerById (id);
   customer.SetFirstName(newFirstName);
   repository.Save(customers);
   return true;
}
bool CustomerManager::UpdateLastName (int id, const std::string& newLastName)
{
   Customer& customer = FindCustomerById (id);
   customer.SetLastName(newLastName);
   repository.Save(customers);
   return true;
}
bool CustomerManager::UpdateDateOfBirth (int id, const Date& newDateOfBirth)
{
   Customer& customer = FindCustomerById (id);
   customer.SetDateOfBirth(newDateOfBirth);
   repository.Save(customers);
   return true;
}
bool CustomerManager::UpdateGender (int id, customerTypes::Gender newGender)
{
   Customer& customer = FindCustomerById (id);
   customer.SetGender(newGender);
   repository.Save(customers);
   return true;
}
//bool CustomerManager::UpdateCustomerStatus (int id, customerTypes::CustomerStatus newStatus) {
//   std::vector<Customer>::iterator it = FindCustomerById (id);
//   if (it == customers.end()) return false;
//   it->SetCustomerStatus(newStatus);
//   repository.Save(customers);
//   return true;
//}
bool CustomerManager::UpdateMemberLevel (int id, customerTypes::MemberLevel newLevel)
{
   Customer& customer = FindCustomerById (id);
   customer.SetMemberLevel(newLevel);
   repository.Save(customers);
   return true;
}
bool CustomerManager::UpdateEmail (int id, const std::string& newEmail)
{
   Customer& customer = FindCustomerById (id);
   customer.SetEmail(newEmail);
   repository.Save(customers);
   return true;
}
bool CustomerManager::UpdateAddress (int id, const Address& newAddress)
{
   Customer& customer = FindCustomerById (id);
   customer.SetAddress(newAddress);
   repository.Save(customers);
   return true;
}

bool CustomerManager::UpdateStatus (int id, customerTypes::CustomerStatus newStatus)
{
   Customer& customer = FindCustomerById (id);
   customer.SetCustomerStatus(newStatus);
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
   auto it = std::find_if (customers.begin(), customers.end(), [id] (const Customer& customer) {
         return customer.GetId() == id;
      }
   );
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
   auto it = find_if (customers.begin(), 
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

bool CustomerManager::SetPreferredContact (int id, ContactData::ContactType type)
{
   for (Customer& customer : customers) {
      if (customer.GetId() == id) {
         std::cout << "customer found\n";

         bool success = customer.SetPreferredContact(type);
         if (success) {
            repository.Save(customers);
         }

         return success;
      }
   }
   std::cout << "customer not found\n";
   return false;
}


// Learning example for Strategy Pattern.
// Sorting may later be moved to database queries using ORDER BY.
void CustomerManager::SortCustomers (const CustomerSortStrategy& strategy)
{
   strategy.Sort(customers);
}
