#pragma once

class CustomerManagerUI;

class CustomerManager
{
private:
   std::vector<Customer> customers;
   CustomerManagerUI* ui;
   
public:
   std::vector<Customer>::iterator FindCustomerById(const int& searchId);

   int GenerateCustomerId();
   void Add(Customer& newCustomer);
   void Update();
   void Remove();
   void Show();

};