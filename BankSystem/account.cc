
#include "account.h"
#include <random>

using namespace std;
using namespace BankSystem;

namespace {
  unsigned long long GenerateRandomNumber(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<unsigned long long> distrib(100000000000, 999999999999);

    return distrib(gen);
  }
}

// init
Account::Account() {}
Account::Account(const string& name){
  account_info_.accId_ = GenerateRandomNumber();
  account_info_.balance_ = 0;
  account_info_.cusName_ = name;
  account_info_.init_status_ = true;
  account_info_.account_name_ = "기본 계좌";
}
Account::Account(Info account_info) : account_info_(account_info) {}
Account::~Account() {}

// get set method
const unsigned long long Account::getId() const { return account_info_.accId_; }
void Account::SetId(const unsigned long long accId) { account_info_.accId_ = accId; }
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