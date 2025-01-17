#include "customer.h"
#include "account.h"

using namespace std;
using namespace BankSystem;

Customer::Customer(const string& name) : name_(name) { account_.SetName(name); }
Customer::Customer(const string& name, const Account::Info account_info) {
    SetAccount(account_info);
}
Customer::~Customer() {}

const string Customer::GetCustomerName() const { return name_; }

Account& Customer::GetAccount() { return account_; }

void Customer::SetAccount(const Account::Info& account_info) {
    account_.setInitStatus(true);
    account_.SetId(account_info.accId_);
    account_.SetBalane(account_info.balance_);
    account_.SetName(account_info.cusName_);
}