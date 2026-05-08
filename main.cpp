#include "Date.h"
#include "Customer.h"
#include "CustomerManager.h"
#include "CustomerManagerUI.h"
#include "CustomerRepository.h"
#include "OutputFactory.h"
#include<vector>
#include<iostream>


int main()
{
   std::unique_ptr<Logger> logger = std::make_unique<Logger>("log.txt");
   std::unique_ptr<CustomerRepository> repository = std::make_unique<FileCustomerRepository>("customer.txt", *logger);
   std::vector<Customer> customers = repository->Load();
   
   CustomerManager manager(*repository, customers);

   std::unique_ptr<ConsoleOutput> output = std::make_unique<ConsoleOutput>();
   

   CustomerManagerUI ui(manager, *output, *logger);

   
   logger->Print("Program started");

   ui.Run();
   //repository->Save(manager.GetCustomers());
}
