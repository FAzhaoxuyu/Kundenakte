#include "CustomerSortStrategy.h"
#include<algorithm>

void SortByLastName :: Sort (std::vector<Customer>& customers) const
{
   std::sort(customers.begin(), customers.end(),
      [](const Customer& a, const Customer& b)
      {return a.GetLastName() < b.GetLastName();
      });
}

void SortById :: Sort (std::vector<Customer>& customers) const
{
   std::sort (customers.begin(), customers.end(),
      [](const Customer& a, const Customer& b) 
      {return a.GetId() < b.GetId();});
}