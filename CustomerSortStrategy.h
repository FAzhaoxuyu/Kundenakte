#pragma once
#include "Customer.h"

// Learning example for Strategy Pattern.
// Sorting may later be moved to database queries using ORDER BY.

class CustomerSortStrategy
{
public:
   virtual void Sort(std::vector<Customer>& customers) const = 0;
};

class SortByLastName : public CustomerSortStrategy
{
public:
   void Sort(std::vector<Customer>& customers)  const override;
};

class SortById : public CustomerSortStrategy
{
public:
   void Sort(std::vector<Customer>& customers) const override;
};