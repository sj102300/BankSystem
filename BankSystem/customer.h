#pragma once

#include <string>
#include <vector>

#include "account.h"

namespace BankSystem {
class Customer {
 public:
  Customer(const std::string& name);
  ~Customer();
  
  const int GetAccountSize() const;
  const std::string& GetCustomerName() const;
  Account& GetAccount(int idx);

  //validation
  bool CheckAccountIdx(int idx);
  bool hasAccount();

  //기능
  void OpenAccount(const std::string& name);
  void OpenAccount(Account::Info account_info_);
  void Deposit(int accIdx, int money);
  void Withdraw(int accIdx, int money);
  void PrintAccounts(); 

  //삭제할때 쓸거
  bool FindAccountByAccId(int accId);
  int CloseAccount(int accId);

 private:
  std::string name_;
  std::vector<Account> accounts_;
};
}  // namespace BankSystem