#pragma once

#include <memory>
#include <string>
#include <random>

#include "bank/bank_database.h"
#include "customer.h"

namespace BankSystem {
class ATM {
 private:
  BankDatabase* db;
  std::string getCurrentTimestamp();
  // 12자리 랜덤 계좌번호 생성
  std::string generateAccountNumber();
  std::random_device rd;
  std::mt19937_64 gen;

 public:
  ATM();
  ~ATM();
  int GetOptionCode();
  void MakeAccount(Customer& cus);
  void Deposit(Customer& cus);
  void Withdraw(Customer& cus);
  void PrintAccountInfo(Customer& cus);
  void CustomerVisit(Customer& cus);
};
}  // namespace BankSystem