#include "atm.h"

#include <iostream>

#include "account.h"

using namespace std;
using namespace BankSystem;

int ATM::GetOptionCode() {
  int option;
  cout << "-----Menu-----" << endl;
  cout << "1. 계좌개설" << endl;
  cout << "2. 입 금" << endl;
  cout << "3. 출 금" << endl;
  cout << "4. 계좌정보 전체 출력" << endl;
  cout << "5. 입출금 내역 출력" << endl;
  cout << "-------------" << endl;
  cout << "0. 프로그램 종료" << endl;
  cout << "선택: ";
  cin >> option;
  cout << "-------------" << endl;
  return option;
}

void ATM::MakeAccount(Customer& cus) {
  BankSystem::Account new_account(cus.GetCustomerName());
  cout << "계좌 명을 입력해주세요 : ";
  std::string account_name;
  cin >> account_name;
  new_account.setAccountName(account_name);
  new_account.AccountInfo();

  cus.addAccount(new_account);
  return;
}

void ATM::Deposit(Customer& cus) {
  cus.printAccountList();
  cout << "입금할 계좌를 선택해주세요 : ";

  int account_idx = 0;
  cin >> account_idx;
  if (cus.checkAccountsIndex(account_idx) == false) {
    return;
  }

  cout << "입금할 금액을 입력해주세요 : ";

  int input_money = 0;
  cin >> input_money;
  cus.Deposit(account_idx, input_money);
  cout << "입금 후 잔액: " << cus.GetAccount(account_idx)->getBalance() << endl;
  return;
}

void ATM::Withdraw(Customer& cus) {
  cus.printAccountList();
  cout << "출금할 계좌를 선택해주세요 : ";

  int account_idx = 0;
  cin >> account_idx;

  cout << "출금할 금액을 입력해주세요 : ";

  int output_money = 0;
  cin >> output_money;
  cus.Withdraw(account_idx, output_money);
  cout << "입금 후 잔액: " << cus.GetAccount(account_idx)->getBalance() << endl;
  return;
}

void ATM::PrintAccountInfo(Customer& cus) {
  cus.printAccountList();
  return;
}

// void ATM::LoggingAccountHistory(const Account& account, int money,
//                                 Bank_Option type) {
//   auto logging = account_history_list[account.getId()];
//   logging.emplace_back();
// }

void ATM::PrintAccountHistory(Customer& cus) {
  cus.printAccountList();
  cout << "입출금 내역을 확인할 계좌를 선택해주세요 : ";

  int account_idx;
  cin >> account_idx;

  const auto account = cus.GetAccount(account_idx);
  const auto account_id = account->getId();

  cout << "계좌 ID : " << account_id << "의 입출금 내역" << endl;
  for (const auto history : account_history_list[account_id]) {
    cout << history << endl;
  }
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
        //   case (Bank_Option::PRINT_HISTORY):
        //     PrintAccountHistory();
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