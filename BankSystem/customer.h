#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "account.h"

namespace BankSystem {
class Customer {
 public:
  Customer(const std::string& name);
  ~Customer();

  const bool checkAccountsIndex(int n) const;

  const std::string& GetCustomerName() const;
  const Account* GetAccount(int account_idx) const;
  void Deposit(int account_idx, int money);
  void Withdraw(int account_idx, int money);
  void createAccount(int account_idx, const Account::Info& account_info);
  void addAccount(const Account& account);
  void printAccountList();

 private:
  std::string name_;
  std::vector<Account> accounts_;
};
}  // namespace BankSystem