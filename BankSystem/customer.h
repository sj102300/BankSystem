#pragma once

#include <string>
#include <vector>

#include "account.h"

namespace BankSystem {
class Customer {
 public:
  Customer(const std::string& name);
  ~Customer();
  
  const int getAccountCnt() const;
  const std::string GetCustomerName() const;

  Account& GetAccount(int idx);
  void OpenAccount(Account::Info account_info_);
  int CloseAccount(int accId);
  bool hasAccount();
  void PrintAccounts();
  int DepositByAccId(int accId, int money);
  int WithdrawByAccId(int accId, int money);
  bool FindAccountByAccId(int accId);

 private:
  std::string name_;
  std::vector<Account> accounts_;
  int account_cnt_;
};
}  // namespace BankSystem