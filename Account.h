#pragma once

enum class AccountType
{
   Girokonto,
   Tagesgeld,
   Sparkonto,
   Festgeld,
   Depot,
   Geschaeftskonto
};

class Account
{
public:
   Account ();
   Account (int accountId,
      int customerId,
      AccountType accountType,
      double balance) : accountId(accountId),
      customerId(customerId),
      accountType(accountType),
      balance(balance) {}

   int accountId;
   int customerId;
   AccountType accountType;
   double balance;

   int GetAccountId () const;
   int GetCustomerId () const;
   AccountType GetAccountType () const;
   double GetBalance () const;

   void Deposit (double amount);
   bool Withdraw (double amount);
};