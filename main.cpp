#include "Date.h"
#include "Customer.h"
#include "CustomerManager.h"
#include "CustomerManagerUI.h"
#include "CustomerRepository.h"
#include<vector>
#include<iostream>


int main()
{
   CustomerRepository repository;
   std::vector<Customer> customers = repository.LoadFromFile("customer.txt");
   CustomerManager manager(repository, customers);
   CustomerManagerUI ui(manager);
   ui.Run();
   CustomerRepository::SaveToFile("customer.txt", manager.GetCustomers());
}
