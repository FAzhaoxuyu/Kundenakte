#include "Account.h"

Account::Account () : accountId(0), customerId(0), accountType(AccountType::Girokonto), balance(0.0) {};

int Account::GetAccountId() const
{
   return accountId;
}

int Account::GetCustomerId() const
{
   return customerId;
}

AccountType Account::GetAccountType() const
{
   return accountType;
}

double Account::GetBalance() const
{
   return balance;
}

void Account::Deposit(double amount)
{
   if (amount > 0) {
      balance += amount;
   }
}

bool Account::Withdraw(double amount)
{
   if (amount <= 0) {
      return false;
   }

   if (balance < amount) {
      return false;
   }

   balance -= amount;
   return true;
}