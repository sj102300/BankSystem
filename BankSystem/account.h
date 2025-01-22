#pragma once

#include <string>

namespace BankSystem {
class Account {
 public:
  struct Info
  {
    unsigned long long accId_ = 0;
    int balance_ = 0;
    std::string account_name_;
    std::string cusName_;
    bool init_status_;
  };

  Account();
  Account(const std::string& name);
  Account(Info account_info);
  ~Account();

  // get set method
  const unsigned long long getId() const;
  void SetId(const unsigned long long accId);
  const int getBalance() const;
  void SetBalane(const int balance);
  const std::string getName() const;
  void SetName(const std::string& cusName);
  const Info getInfo() const;

  // 기능
  int DepositBalance(int money);
  int WithdrawBalance(int money);

 private:
  Info account_info_;
};
};  // namespace BankSystem