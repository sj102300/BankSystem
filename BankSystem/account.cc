
#include "account.h"

using namespace std;
using namespace BankSystem;

// init
Account::Account() {}
Account::Account(Info account_info) : account_info_(account_info) {}

Account::~Account() {}

// get set method
const int Account::getId() const { return account_info_.accId_; }
void Account::SetId(const int accId) { account_info_.accId_ = accId; }
const int Account::getBalance() const { return account_info_.balance_; }
void Account::SetBalane(const int balance) { account_info_.balance_ = balance; }
const std::string Account::getName() const { return account_info_.cusName_; }
void Account::SetName(const std::string& cusName) { account_info_.cusName_ = cusName; }
const Account::Info Account::getInfo() const { return account_info_; }

// 기능
int Account::DepositBalance(int money) {
  account_info_.balance_ += money;
  return account_info_.balance_;
}

int Account::WithdrawBalance(int money) {
  if (account_info_.balance_ < money) return -1;
  account_info_.balance_ -= money;
  return account_info_.balance_;
}