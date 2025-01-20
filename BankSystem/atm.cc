#include <iostream>

#include "atm.h"
#include "common_option.h"

using namespace std;
using namespace BankSystem;

int ATM::GetOptionCode() {
  int option;
  cout << "-----Menu-----" << endl;
  cout << "1. 계좌개설" << endl;
  cout << "2. 입 금" << endl;
  cout << "3. 출 금" << endl;
  cout << "4. 계좌정보 전체 출력" << endl;
  cout << "5. 프로그램 종료" << endl;
  cout << "선택: ";
  cin >> option;
  cout << "-------------" << endl;
  return option;
}

void ATM::MakeAccount(Customer& cus) {

  Account::Info account_info;
  cout << "계좌 ID를 입력해주세요: ";
  cin >> account_info.accId_;
  cout << "잔액을 입력해주세요: ";
  cin >> account_info.balance_;
  account_info.cusName_ = cus.GetCustomerName();

  cus.OpenAccount(account_info);
  cout << "계좌 개설이 완료되었습니다" << endl;
  return;
}

void ATM::Deposit(Customer& cus) {
  if (!cus.hasAccount()) {
    cout << "계좌가 없습니다!\n" << endl;
    return;
  }

  cus.PrintAccounts();
  int accId;
  cout<<"입금하실 통장 ID를 입력해주세요: ";

  while(true){
    cin>>accId;
    if(cus.FindAccountByAccId(accId))   break;
    cout<<"다시 입력해주세요: ";
  }

  int money = 0;
  cout << "입금할 금액을 입력하세요: ";
  while (true) {
    cin >> money;
    if (money > 0) break;
    cout << "다시 입력해주세요: ";
  }
  int result = cus.DepositByAccId(accId, money);
  if (result == -1){
    cout<<"입금에 실패했습니다."<<endl;
    return;
  }
  cout << "입금 후 잔액: " << result << endl;
  return;
}

void ATM::Withdraw(Customer& cus) {
  if (!cus.hasAccount()) {
    cout << "계좌가 없습니다!\n" << endl;
    return;
  }
  cus.PrintAccounts();
  int idx;
  cout<<"출금하실 통장 번호를 입력해주세요: ";

  while(true){
    cin>>idx;
    if(0 < idx && idx <= cus.getAccountCnt())   break;
    cout<<"다시 입력해주세요: ";
  }
  
  Account &acctmp = cus.GetAccount(idx-1);
  int money = 0;
  int cusBalance = acctmp.getBalance();
  cout << "현재 잔액: " << cusBalance << endl;
  cout << "출금할 금액을 입력하세요: ";
  while (true) {
    cin >> money;
    if (money < cusBalance) break;
    cout << "잔액이 부족합니다. 다시 입력해주세요: ";
  }
  cout << "출금 후 잔액: " << acctmp.WithdrawBalance(money) << endl;
  return;
}

void ATM::PrintAccountInfo(Customer& cus) {
  if (!cus.hasAccount()) {
    cout << "계좌가 없습니다!\n" << endl;
    return;
  }

  for(int i=0;i<cus.getAccountCnt();++i){
    Account& acc = cus.GetAccount(i);
    cout << i+1<< ". 계좌 ID: " << acc.getId() << " / 잔액: " << acc.getBalance() << endl;
  }
  return;
}

void ATM::CustomerVisit(Customer& cus) {
  int option = 0;
  while (option != 5) {
    option = GetOptionCode();
    switch (option) {
      case (Bank_Option::MAKE):
        MakeAccount(cus);
        break;
      case (Bank_Option::DEPOSIT):
        Deposit(cus);
        break;
      case (Bank_Option::WITHDRAW):
        Withdraw(cus);
        break;
      case (Bank_Option::INQUIRE):
        PrintAccountInfo(cus);
        break;
      case (Bank_Option::EXIT):
        break;
      default:
        cout << "잘못된 입력입니다." << endl;
    }
    cout << endl;
  }
  cout << "종료" << endl;
  return;
}
