#include <iostream>
#include "customer.h"
#include "account.h"

using namespace std;
using namespace BankSystem;

Customer::Customer(const string& name) : name_(name), account_cnt_(0) {}
Customer::~Customer() {}

const string Customer::GetCustomerName() const { return name_; }
const int Customer::getAccountCnt() const{return account_cnt_;}
Account& Customer::GetAccount(int idx) { return accounts_[idx]; }

void Customer::OpenAccount(Account::Info account_info_){
    accounts_.push_back(account_info_);
    ++account_cnt_;
    return;
}

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
            --account_cnt_;
            return accId;
        }
    }
    //못찾았았음
    return -1;
}

bool Customer::hasAccount(){
    return accounts_.size() != 0;
}

void Customer::PrintAccounts(){
    for (int i=0;i<accounts_.size();++i){
        cout<<i+1<<". "<<accounts_[i].getId()<<" ";
    }
    cout<<endl;
    return;
}

int Customer::DepositByAccId(int accId, int money){

    for(auto it = accounts_.begin(); it!=accounts_.end(); ++it){
        if(it->getId() == accId){
            it->SetBalane(it->getBalance() + money);
            return it->getBalance();
        }
    }
    return -1;
}

int Customer::WithdrawByAccId(int accId, int money){
    for(auto it = accounts_.begin(); it!=accounts_.end(); ++it){
        if(it->getId() == accId){
            it->SetBalane(it->getBalance() - money);
            return it->getBalance();
        }
    }
    return -1;
}