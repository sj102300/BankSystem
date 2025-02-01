#pragma once

#include <iostream>
#include <string>
#include <random>

// #include "bank/bank_database.h"
// #include "customer.h"

namespace BankSystem {
class ATM {
 public:
  int GetOptionCode();
  void CustomerVisit(int cusId);
  void MakeAccount(int cusId);
  void Deposit(int cusId);
  void Withdraw(int cusId);
  void PrintAccountInfo(int cusId);
  void Welcome();
};
}  // namespace BankSystem