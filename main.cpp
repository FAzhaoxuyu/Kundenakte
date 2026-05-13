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
   std::unique_ptr<LogOutput> logger = std::make_unique<LogOutput>("log.txt");
   std::unique_ptr<CustomerRepository> repository = std::make_unique<FileCustomerRepository>("customer.txt", *logger);
   std::vector<Customer> customers = repository->Load();

   CustomerManager manager(*repository, customers);
   std::unique_ptr<Output> console = std::make_unique<ConsoleOutput>();
   std::unique_ptr<Output> multiOutput = std::make_unique<MultiOutput>(*console, *logger);
   
   CustomerManagerUI ui(manager, *logger, *console, *multiOutput);

   logger->Print("Program started");

   ui.Run();
  
}
