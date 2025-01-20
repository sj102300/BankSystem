
#include "account.h"

#include <iostream>
#include <random>

using namespace std;
using namespace BankSystem;

namespace {
long long generateRandomNumber() {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<long long> distrib(100000000000, 999999999999);

  // 난수 생성
  return distrib(gen);
}
}  // namespace

// init
Account::Account() {}

Account::Account(const string& name) {
  account_info_.cusName_ = name;
  account_info_.accId_ = generateRandomNumber();
  account_info_.balance_ = 0;
  account_info_.init_status_ = true;
  account_info_.account_name_ = "기본 계좌";
}

Account::Account(Info account_info) : account_info_(account_info) {}

Account::~Account() {}

// get set method
const bool Account::getInitStatus() const { return account_info_.init_status_; }
void Account::setInitStatus(const bool status) {
  account_info_.init_status_ = status;
}
const long long Account::getId() const { return account_info_.accId_; }
void Account::SetId(const long long accId) { account_info_.accId_ = accId; }
const int Account::getBalance() const { return account_info_.balance_; }
void Account::SetBalane(const int balance) { account_info_.balance_ = balance; }
const std::string Account::getUserName() const {
  return account_info_.cusName_;
}
void Account::SetUserName(const std::string& cusName) {
  account_info_.cusName_ = cusName;
}
const std::string Account::getAccountName() const {
  return account_info_.account_name_;
}
void Account::setAccountName(const std::string& account_name) {
  account_info_.account_name_ = account_name;
}

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

const void Account::AccountInfo() const {
  cout << "계좌 ID   : " << account_info_.accId_ << endl;
  cout << "계좌 별칭 : " << account_info_.account_name_ << endl;
  cout << "이름      : " << account_info_.cusName_ << endl;
  cout << "잔액      : " << account_info_.balance_ << endl;
  return;
}