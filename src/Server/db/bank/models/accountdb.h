#pragma once
#include <sqlite_orm/sqlite_orm.h>

#include <string>
#include "customerdb.h"

using namespace sqlite_orm;

class BankDatabase;

struct Account
{
    int accId;          // 자동 증가 primary key
    std::string accNum; // 12자리 계좌번호
    unsigned int cusId;
    unsigned int balance;
    unsigned int accountType;
    bool status;
    std::string created_at;

    static auto getTableDefinition()
    {
        return make_table(
            "Account",
            make_column("accId", &Account::accId, primary_key().autoincrement()),
            make_column("accNum", &Account::accNum, unique(), check(length(&Account::accNum) == 12)),
            make_column("cusId", &Account::cusId),
            make_column("status", &Account::status, default_value(true)),
            make_column("accountType", &Account::accountType),
            make_column("createdAt", &Account::created_at),
            foreign_key(&Account::cusId).references(&Customer::cusId));
    }
};

class AccountDB
{
private:
    static void MakeWithdrawLog(Account &targetAcc, unsigned int withdraw_money);
    static void MakeDepositLog(Account &targetAcc, unsigned int deposit_money);

public:
    AccountDB();
    static bool isExistAccId(std::string &accId);
    static Account CreateAccount(int cusId, unsigned int account_type);
    static std::vector<Account> GetAccountsByCusId(int cusId);
    static bool DepositBalanceByAccId(std::string &accId,
                                      unsigned int deposit_amount, int cusId);
    static bool WithdrawBalanceByAccId(std::string &accId,
                                       unsigned int withdraw_amount, int cusId);
    static void UpdateAccount(Account &targetAcc);
    static void DeleteAccount(std::string accId);
};