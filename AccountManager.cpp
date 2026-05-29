#include "AccountManager.h"
#include "Account.h"
#include<vector>
#include<algorithm>
#include<optional>


int AccountManager::GenerateAccountId()
{
   if (accounts.empty()) {
      return 1;
   }
 
   auto maxIt = std::max_element(accounts.begin(), accounts.end(),
      [](Account& a, Account& b)
      {return a.GetAccountId() < b.GetAccountId(); });

   return maxIt->GetAccountId() + 1;
};

void AccountManager::CreateAccount(int accountId, int customerId, AccountType accountType, double balance)
{
   int newId = GenerateAccountId();
   Account newAccount(newId, customerId, accountType, 0.0);
   accounts.push_back(newAccount);
}

Account* AccountManager::FindAccountById(int accountId)
{
   auto it = std::find_if(accounts.begin(), accounts.end(), [accountId](const Account& account) {return account.GetAccountId() == accountId; });
   if (it != accounts.end()) {
      return &(*it);
   }
   return nullptr;
}

bool AccountManager::Deposit(int accountId, double amount)
{
   if (amount < 0) {
      return false;
   }

   Account* account = FindAccountById(accountId);

   if (account == nullptr) {
      return false;
   }

   account->Deposit(amount);
   return true;
}
   
bool AccountManager::Withdraw(int accountId, double amount)
{
   if (amount < 0) {
      return false;
   }

   Account* account = FindAccountById(accountId);

   if (account == nullptr) {
      return false;
   }

   account->Withdraw(amount);
   return true;
}

bool AccountManager::Transfer(int fromAccountId, int toAccountId, double amount)
{
   if (amount < 0) {
      return false;
   }

   Account* fromAccount = FindAccountById(fromAccountId);
   Account* toAccount = FindAccountById(toAccountId);

   if (fromAccount == nullptr || toAccount == nullptr) {
      return false;
   }

   bool withdrawSuccess = fromAccount->Withdraw(amount);

   if (!withdrawSuccess) {
      return false;
   }

   toAccount->Deposit(amount);
   return true;
}