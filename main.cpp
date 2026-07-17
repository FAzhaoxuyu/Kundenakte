#include "Date.h"
#include "Customer.h"
#include "CustomerManager.h"
#include "CustomerManagerUI.h"
#include "CustomerRepository.h"
#include "OutputFactory.h"
#include<vector>
#include<iostream>

#include <SqliteWrapper.hpp>


int main ()
{
   std::unique_ptr<LogOutput> logger = std::make_unique<LogOutput> ("log.txt");
   auto timeLogger = std::make_unique<TimeStampDecorator> (*logger);
   auto errorTimeLogger = std::make_unique<ErrorDecorator> (*timeLogger);

   std::unique_ptr<CustomerRepository> repository = std::make_unique<FileCustomerRepository> ("customer.csv", *logger);
   std::vector<Customer> customers = repository->Load ();

   CustomerManager manager (*repository, customers);
   std::unique_ptr<Output> console = std::make_unique<ConsoleOutput> ();
   std::unique_ptr<Output> multiOutput = std::make_unique<MultiOutput> (*console, *timeLogger);
   
   CustomerManagerUI ui (manager, *logger, *console, *multiOutput, *errorTimeLogger); //?ui????????????

   timeLogger->Print ("Program started");
   ui.Run ();
   timeLogger->Print ("Program ended");

   try {
      Sqlite::SqliteConnection connection("test.db");

      sqliteExecute(
         connection,
         "CREATE TABLE IF NOT EXISTS Test ("
         "Id INTEGER PRIMARY KEY, "
         "Name TEXT)"
      );

      std::cout << "Database test successful.\n";
   }
   catch (const Sqlite::exception& e) {
      std::cout << e.errorMessage_
         << " ("
         << e.errorCode_
         << ")\n";
   }
}
