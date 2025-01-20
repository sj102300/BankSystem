#include "customer.h"

#include <iostream>

#include "account.h"

using namespace std;
using namespace BankSystem;

Customer::Customer(const string& name) {
  name_ = name;
  accounts_.emplace_back(BankSystem::Account(name));
}
Customer::~Customer() {}

const string& Customer::GetCustomerName() const { return name_; }

const Account* Customer::GetAccount(int account_idx) const {
  if (checkAccountsIndex(account_idx)) {
    return &accounts_.at(account_idx - 1);
  }
  return nullptr;  // 유효하지 않은 경우 nullptr 반환
}

void Customer::Deposit(int account_idx, int money) {
  if (checkAccountsIndex(account_idx)) {
    accounts_.at(account_idx - 1).DepositBalance(money);
  }
}

void Customer::Withdraw(int account_idx, int money) {
  if (checkAccountsIndex(account_idx)) {
    accounts_.at(account_idx - 1).WithdrawBalance(money);
  }
}

void Customer::createAccount(int account_idx,
                             const Account::Info& account_info) {
  accounts_[account_idx].setInitStatus(true);
  accounts_[account_idx].SetId(account_info.accId_);
  accounts_[account_idx].SetBalane(account_info.balance_);
  accounts_[account_idx].SetUserName(account_info.cusName_);
}

void Customer::addAccount(const Account& account) {
  accounts_.emplace_back(account);
}

void Customer::printAccountList() {
  int idx = 0;
  cout << "[총 계좌 갯수 : " << accounts_.size() << "]" << endl;
  for (const auto& account : accounts_) {
    cout << ++idx << ". 계좌 idx--" << endl;
    account.AccountInfo();
    cout << "" << endl;
  }
}

const bool Customer::checkAccountsIndex(int n) const {
  if (accounts_.size() >= n) {
    return true;
  }
  cout << "계좌의 idx범위를 벗어났습니다." << endl;
  return false;
}