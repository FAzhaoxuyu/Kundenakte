#pragma once
#include "Account.h"
#include "TransactionType.h"

class Transaction
{
public:
   Transaction(int transactionId,
      Account fromAccount,
      Account toAccount,
      double amount,
      TransactionType type) :
      transactionId(transactionId),
      fromAccount(fromAccount),
      toAccount(toAccount),
      amount(amount),
      type(type) {};

   int GetTransactionId() const;



private:
   int transactionId;
   Account fromAccount;
   Account toAccount;
   double amount;
   TransactionType type;
};