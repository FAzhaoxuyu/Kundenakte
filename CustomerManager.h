#pragma once
#include<vector>
#include "Customer.h"
#include "CustomerRepository.h"
#include<optional>

class CustomerManager
{
private:
   std::vector<Customer> customers;
   CustomerRepository& repository;

public: 
   CustomerManager(CustomerRepository& repository, const std::vector<Customer>& customers) : repository(repository), customers(customers) {};
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
   bool UpdateStatus(int id, CustomerStatus newStatus);

   bool Exist(int id) const;

   bool RemoveById(int id);

  

   //void SaveToFile(const std::string& filename) const;
   //void LoadFromFile(const std::string& filename);
};