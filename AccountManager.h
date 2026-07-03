#pragma once
#include "Account.h"
#include "Transaction.h"
#include<vector>

class AccountManager
{
public:
   int GenerateAccountId ();
   void CreateAccount (int accountId, int customerId, AccountType accountType, double balance);
   Account& FindAccountById (int accountId);

   bool Deposit (int accountId, double amount);
   bool Withdraw (int accountId, double amount);

   const std::vector<Account>& GetAccounts() const;

   bool Transfer (int fromAccountId, int toAccountId, double amount);
private:
   std::vector<Account> accounts;
   std::vector<Transaction> transactions;
};
