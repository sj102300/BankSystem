#pragma once

#include <string>

namespace BankSystem {
class Account {
 public:
  struct Info
  {
    bool init_status_ = false;
    int accId_ = 0;
    int balance_ = 0;
    std::string cusName_;
  };

  Account();
  Account(Info account_info);
  ~Account();

  // get set method
  const bool getInitStatus() const;
  void setInitStatus(const bool status);
  const int getId() const;
  void SetId(const int accId);
  const int getBalance() const;
  void SetBalane(const int balance);
  const std::string getName() const;
  void SetName(const std::string& cusName);

  // 기능
  int DepositBalance(int money);
  int WithdrawBalance(int money);

 private:
  Info account_info_;
};
};  // namespace BankSystem