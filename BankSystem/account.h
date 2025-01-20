#pragma once

#include <string>

namespace BankSystem {
class Account {
 public:
  struct Info {
    bool init_status_ = false;
    long long accId_ = 0;
    int balance_ = 0;
    std::string cusName_;
    std::string account_name_;
  };

  Account();
  Account(const std::string& name);
  Account(Info account_info);
  ~Account();

  // get set method
  const bool getInitStatus() const;
  void setInitStatus(const bool status);
  const long long getId() const;
  void SetId(const long long accId);
  const int getBalance() const;
  void SetBalane(const int balance);
  const std::string getUserName() const;
  void SetUserName(const std::string& cusName);
  const std::string getAccountName() const;
  void setAccountName(const std::string& cusName);

  // 기능
  int DepositBalance(int money);
  int WithdrawBalance(int money);
  const void AccountInfo() const;

 private:
  Info account_info_;
};
};  // namespace BankSystem