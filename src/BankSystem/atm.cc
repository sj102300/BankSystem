#include "atm.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

#include "common_option.h"

using namespace std;
using namespace BankSystem;

random_device rd;
ATM::ATM() : db(BankDatabase::getInstance()), gen(rd()) { db->initStorage(); }

ATM::~ATM() {}

std::string ATM::generateAccountNumber() {
  // 12자리 랜덤 계좌번호 생성
  uniform_int_distribution<int64_t> dis(100'000'000'000, 999'999'999'999);
  int64_t accountNumber;
  auto& storage = db->getStorage();

  do {
    accountNumber = dis(gen);
    // 중복 체크
    auto existing = storage.get_all<::Account>(
        where(c(&::Account::accId) == std::to_string(accountNumber)));
    if (existing.empty()) {
      break;
    }
  } while (true);

  return std::to_string(accountNumber);
}

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
  auto& storage = db->getStorage();

  // 고객 정보 저장 또는 조회
  auto customers = storage.get_all<::Customer>(
      where(c(&::Customer::cus_name) == cus.GetCustomerName()));

  int cusId;
  if (customers.empty()) {
    // 새 고객 등록
    ::Customer newCustomer{-1, cus.GetCustomerName()};
    cusId = storage.insert(newCustomer);
  } else {
    cusId = customers[0].cusId;
  }

  // 계좌 생성 (랜덤 계좌번호 사용)
  ::Account newAccount{
      -1,                      // id (자동 증가)
      generateAccountNumber(), // accId (12자리 랜덤 번호)
      cusId,                  // cusId
      0,                      // balance
      1,                      // account_type (일반계좌)
      true,                   // status
      getCurrentTimestamp()   // created_at
  };

  storage.insert(newAccount);
  cout << "계좌 개설이 완료되었습니다. 계좌번호: " << newAccount.accId << endl;
}

void ATM::Deposit(Customer& cus) {
  auto& storage = db->getStorage();

  // 고객의 계좌 목록 조회
  auto customers = storage.get_all<::Customer>(
      where(c(&::Customer::cus_name) == cus.GetCustomerName()));

  if (customers.empty()) {
    cout << "고객 정보를 찾을 수 없습니다!" << endl;
    return;
  }

  auto accounts = storage.get_all<::Account>(
      where(c(&::Account::cusId) == customers[0].cusId &&
            c(&::Account::status) == true));

  if (accounts.empty()) {
    cout << "계좌가 없습니다!\n" << endl;
    return;
  }

  // 계좌 목록 출력
  cout << "계좌 목록:" << endl;
  for (size_t i = 0; i < accounts.size(); ++i) {
    cout << i + 1 << ". 계좌 ID: " << accounts[i].accId
         << " / 잔액: " << accounts[i].balance << endl;
  }

  // 계좌 선택
  int accIdx;
  cout << "입금하실 통장 번호를 입력해주세요: ";
  while (true) {
    cin >> accIdx;
    if (accIdx > 0 && accIdx <= static_cast<int>(accounts.size())) break;
    cout << "다시 입력해주세요: ";
  }

  // 입금 금액 입력
  int money = 0;
  cout << "입금할 금액을 입력하세요: ";
  while (true) {
    cin >> money;
    if (money > 0) break;
    cout << "다시 입력해주세요: ";
  }

  // 거래 처리
  auto& selectedAccount = accounts[accIdx - 1];
  int afterBalance = selectedAccount.balance + money;
  selectedAccount.balance = afterBalance;
  storage.update(selectedAccount);

  // 거래 로그 기록
  ::TransactionLog log{
      -1,                       // logId
      selectedAccount.id,       // accountId
      selectedAccount.accId,    // accId (12자리 계좌번호)
      selectedAccount.cusId,    // cusId
      1,                        // transaction_type (입금)
      money,                    // trade_amount
      afterBalance,             // remaining_balance
      getCurrentTimestamp()     // created_at
  };
  storage.insert(log);

  cout << "입금 후 잔액: " << selectedAccount.balance << endl;
}

void ATM::Withdraw(Customer& cus) {
  auto& storage = db->getStorage();

  // 고객의 계좌 목록 조회
  auto customers = storage.get_all<::Customer>(
      where(c(&::Customer::cus_name) == cus.GetCustomerName()));

  if (customers.empty()) {
    cout << "고객 정보를 찾을 수 없습니다!" << endl;
    return;
  }

  auto accounts = storage.get_all<::Account>(
      where(c(&::Account::cusId) == customers[0].cusId &&
            c(&::Account::status) == true));

  if (accounts.empty()) {
    cout << "계좌가 없습니다!\n" << endl;
    return;
  }

  // 계좌 목록 출력
  cout << "계좌 목록:" << endl;
  for (size_t i = 0; i < accounts.size(); ++i) {
    cout << i + 1 << ". 계좌 ID: " << accounts[i].accId
         << " / 잔액: " << accounts[i].balance << endl;
  }

  // 계좌 선택
  int accIdx;
  cout << "출금하실 통장 번호를 입력해주세요: ";
  while (true) {
    cin >> accIdx;
    if (accIdx > 0 && accIdx <= static_cast<int>(accounts.size())) break;
    cout << "다시 입력해주세요: ";
  }

  auto& selectedAccount = accounts[accIdx - 1];

  // 출금 금액 입력
  int money = 0;
  cout << "현재 잔액: " << selectedAccount.balance << endl;
  cout << "출금할 금액을 입력하세요: ";
  while (true) {
    cin >> money;
    if (money <= selectedAccount.balance) break;
    cout << "잔액이 부족합니다. 다시 입력해주세요: ";
  }

  // 거래 처리
  int afterBalance = selectedAccount.balance - money;
  selectedAccount.balance = afterBalance;
  storage.update(selectedAccount);

  // 거래 로그 기록
  ::TransactionLog log{
      -1,                       // logId
      selectedAccount.id,       // accountId
      selectedAccount.accId,    // accId (12자리 계좌번호)
      selectedAccount.cusId,    // cusId
      2,                        // transaction_type (출금)
      money,                    // trade_amount
      afterBalance,             // remaining_balance
      getCurrentTimestamp()     // created_at
  };
  storage.insert(log);

  cout << "출금 후 잔액: " << selectedAccount.balance << endl;
}

void ATM::PrintAccountInfo(Customer& cus) {
  auto& storage = db->getStorage();

  // 고객의 계좌 목록 조회
  auto customers = storage.get_all<::Customer>(
      where(c(&::Customer::cus_name) == cus.GetCustomerName()));

  if (customers.empty()) {
    cout << "고객 정보를 찾을 수 없습니다!" << endl;
    return;
  }

  auto accounts = storage.get_all<::Account>(
      where(c(&::Account::cusId) == customers[0].cusId &&
            c(&::Account::status) == true));

  if (accounts.empty()) {
    cout << "계좌가 없습니다!\n" << endl;
    return;
  }

  // 계좌 정보 출력
  for (size_t i = 0; i < accounts.size(); ++i) {
    const auto& acc = accounts[i];
    cout << i + 1 << ". 계좌 ID: " << acc.accId << " / 잔액: " << acc.balance
         << endl;

    // 해당 계좌의 거래 내역 조회
    auto logs = storage.get_all<::TransactionLog>(
        where(c(&::TransactionLog::accountId) == acc.id),
        order_by(&::TransactionLog::created_at).desc());

    cout << "   거래 내역:" << endl;
    for (const auto& log : logs) {
      string type = log.transaction_type == 1 ? "입금" : "출금";
      cout << "   - " << type << ": " << log.trade_amount
           << " / 잔액: " << log.remaining_balance
           << " / 시간: " << log.created_at << endl;
    }
    cout << endl;
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
      case (Bank_Option::EXIT):
        break;
      default:
        cout << "잘못된 입력입니다." << endl;
    }
    cout << endl;
  }
  cout << "종료" << endl;
}

// 현재 시간을 문자열로 반환하는 유틸리티 함수
std::string ATM::getCurrentTimestamp() {
  auto now = std::chrono::system_clock::now();
  auto now_time_t = std::chrono::system_clock::to_time_t(now);
  auto now_tm = *std::localtime(&now_time_t);
  std::ostringstream oss;
  oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
  return oss.str();
}