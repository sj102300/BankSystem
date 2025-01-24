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

  cus.OpenAccount(cus.GetCustomerName());
  cout << "계좌 개설이 완료되었습니다" << endl;
  return;
}

void ATM::Deposit(Customer& cus) {
  if (!cus.hasAccount()) {
    cout << "계좌가 없습니다!\n" << endl;
    return;
  }

  cus.PrintAccounts();
  int accIdx;
  cout<<"입금하실 통장 idx를 입력해주세요: ";

  while(true){
    cin>>accIdx;
    if(cus.CheckAccountIdx(accIdx-1))   break;
    cout<<"다시 입력해주세요: ";
  }

  int money = 0;
  cout << "입금할 금액을 입력하세요: ";
  while (true) {
    cin >> money;
    if (money > 0) break;
    cout << "다시 입력해주세요: ";
  }
  cus.Deposit(accIdx - 1, money);
  cout << "입금 후 잔액: " << cus.GetAccount(accIdx-1).getBalance() << endl;
  return;
}

void ATM::Withdraw(Customer& cus) {
  if (!cus.hasAccount()) {
    cout << "계좌가 없습니다!\n" << endl;
    return;
  }
  cus.PrintAccounts();
  int idx;
  cout<<"출금하실 통장 idx를 입력해주세요: ";

  while(true){
    cin>>idx;
    if(cus.CheckAccountIdx(idx))   break;
    cout<<"다시 입력해주세요: ";
  }
  
  Account &targetacc = cus.GetAccount(idx-1);
  int money = 0;
  int cusBalance = targetacc.getBalance();
  cout << "현재 잔액: " << cusBalance << endl;
  cout << "출금할 금액을 입력하세요: ";
  while (true) {
    cin >> money;
    if (money <= cusBalance) break;
    cout << "잔액이 부족합니다. 다시 입력해주세요: ";
  }
  targetacc.WithdrawBalance(money);
  cout << "출금 후 잔액: " << targetacc.getBalance() << endl;
  return;
}

void ATM::PrintAccountInfo(Customer& cus) {
  if (!cus.hasAccount()) {
    cout << "계좌가 없습니다!\n" << endl;
    return;
  }

  for(int i=0;i<cus.GetAccountSize();++i){
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
