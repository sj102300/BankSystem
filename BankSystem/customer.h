#pragma once

#include <string>
#include <vector>

#include "account.h"

namespace BankSystem {
class Customer {
 public:
  Customer(const std::string& name);
  Customer(const std::string& name, const Account::Info account_info);
  ~Customer();
  
  const std::string GetCustomerName() const;
  Account& GetAccount();
  void SetAccount(const Account::Info& account_info);

 private:
  std::string name_;
  Account account_;
};
}  // namespace BankSystem