#include <iostream>
#include <string>
#include "customer.h"
#include "account.h"

using namespace std;
using namespace BankSystem;

Customer::Customer(const string& name) : name_(name) {}
Customer::~Customer() {}

const int Customer::GetAccountSize() const{return accounts_.size();}
const string& Customer::GetCustomerName() const { return name_; }
Account& Customer::GetAccount(int idx) { return accounts_[idx]; }

//validation
bool Customer::CheckAccountIdx(int idx){
    return 0 <= idx && idx < accounts_.size();
}

bool Customer::hasAccount(){
    return accounts_.size() != 0;
}

//기능
void Customer::OpenAccount(const string& name){
    accounts_.push_back(name);
}

void Customer::OpenAccount(Account::Info account_info_){
    accounts_.push_back(account_info_);
    return;
}

void Customer::Deposit(int accIdx, int money){
    accounts_.at(accIdx).DepositBalance(money);
}

void Customer::Withdraw(int accIdx, int money){
    accounts_.at(accIdx).WithdrawBalance(money);
}

void Customer::PrintAccounts(){
    for (int i=0;i<accounts_.size();++i){
        cout<<i+1<<". "<<accounts_.at(i).getId()<<" ";
    }
    cout<<endl;
    return;
}

//삭제 할때 필요. 아직 안쓰는거..
bool Customer::FindAccountByAccId(int accId){
    for(auto account: accounts_){
        if (account.getId() == accId){
            return true;
        }
    }
    return false; 
}

int Customer::CloseAccount(int accId) {
    for (auto it = accounts_.begin(); it != accounts_.end(); ++it) {
        if (it->getId() == accId) {
            accounts_.erase(it);
            return accId;
        }
    }
    return -1;
}
