#include "Date.h"
#include "Customer.h"
#include "CustomerManager.h"
#include "CustomerManagerUI.h"
#include "CustomerRepository.h"
#include<vector>
#include<iostream>


int main()
{
   CustomerRepository* repository = new FileCustomerRepository("customer.txt");
   std::vector<Customer> customers = repository->Load();
   CustomerManager manager(*repository, customers);
   CustomerManagerUI ui(manager);
   ui.Run();
   //repository->Save(manager.GetCustomers());
}
