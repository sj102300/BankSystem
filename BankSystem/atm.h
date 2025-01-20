#pragma once

#include <string>
#include <unordered_map>

#include "common_optino.h"
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
  void PrintAccountHistory(Customer& cus);
  //   void LoggingAccountHistory(const Account& account, int money,
  //                              Bank_Option type);

 private:
  std::unordered_map<long long, std::vector<std::string>> account_history_list;
};
}  // namespace BankSystem