#pragma once

#include <string>
#include "customer.h"

namespace BankSystem {
class ATM {
 public:
  static int GetOptionCode();
  static void MakeAccount(Customer& cus);
  static void Deposit(Customer& cus);
  static void Withdraw(Customer& cus);
  static void PrintAccountInfo(Customer& cus);
  static void CustomerVisit(Customer& cus);
};
}