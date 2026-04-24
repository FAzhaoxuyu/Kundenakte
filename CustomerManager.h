#pragma once
#include "Customer.h"
#include<optional>

class CustomerManagerUI;

class CustomerManager
{
private:
   std::vector<Customer> customers;
public: 
   std::vector<Customer>::iterator FindCustomerById(int searchId);
   const std::vector<Customer>& GetCustomers() const;
   const void Add(Customer& newCustomer);
   int GenerateCustomerId();
   bool IsEmpty() const;
   bool UpdateFirstName(int id, const std::string& newFirstName);
   bool UpdateLastName(int id, const std::string& newLastName);
   bool UpdateDateOfBirth(int id, const Date& newDateOfBirth);
   bool UpdateGender(int id, Gender newGender);
   bool UpdateCustomerStatus(int id, CustomerStatus newStatus);
   bool UpdateMemberLevel(int id, MemberLevel newLevel);
   bool UpdateEmail(int id, const std::string& newEmail);
   bool UpdateAddress(int id, const std::string& newAddress);

   bool RemoveById(int id);

   std::string Serialize() const;
   static std::vector<Customer> DeSerialize(const std::string& line);

   void SaveToFile(const std::string& filename) const;
   static void LoadFromFile(const std::string& filename);
};