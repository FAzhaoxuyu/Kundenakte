#include "Date.h"
#include "Customer.h"
#include "CustomerManager.h"
#include "CustomerManagerUI.h"
#include "CustomerRepository.h"
#include "OutputFactory.h"
#include "SQLiteCustomerRepository.h"

#include<vector>
#include<iostream>




int main ()
{
   std::unique_ptr<LogOutput> logger = std::make_unique<LogOutput> ("log.txt");
   auto timeLogger = std::make_unique<TimeStampDecorator> (*logger);
   auto errorTimeLogger = std::make_unique<ErrorDecorator> (*timeLogger);

   std::unique_ptr<CustomerRepository> fileRepository = std::make_unique<FileCustomerRepository> ("customer.csv", *logger);
   std::vector<Customer> customers = fileRepository->Load ();

   CustomerManager manager (*fileRepository, customers);
   std::unique_ptr<Output> console = std::make_unique<ConsoleOutput> ();
   std::unique_ptr<Output> multiOutput = std::make_unique<MultiOutput> (*console, *timeLogger);
   
   CustomerManagerUI ui (manager, *logger, *console, *multiOutput, *errorTimeLogger); //?ui????????????

   timeLogger->Print ("Program started");
   ui.Run ();
   timeLogger->Print ("Program ended");



   SqliteCustomerRepository sqliteRepository("customers.db");
   std::cout << "Database test successful.\n";
}
