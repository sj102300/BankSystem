#pragma once
#include <sqlite_orm/sqlite_orm.h>

#include <string>
#include "customerdb.h"

using namespace sqlite_orm;

class BankDatabase;

struct Account
{
    int id;            // 자동 증가 primary key
    std::string accId; // 12자리 계좌번호
    int cusId;
    unsigned int balance;
    unsigned int account_type;
    bool status;
    std::string created_at;

    static auto getTableDefinition()
    {
        return make_table(
            "Account",
            make_column("id", &Account::id, primary_key().autoincrement()),
            make_column("accId", &Account::accId, unique(),
                        check(length(&Account::accId) == 12)),
            make_column("cusId", &Account::cusId),
            make_column("balance", &Account::balance, default_value(0)),
            make_column("account_type", &Account::account_type),
            make_column("status", &Account::status, default_value(true)),
            make_column("created_at", &Account::created_at),
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
    static bool DepositBalanceByAccId(std::string& accId,
                                      unsigned int deposit_amount, int cusId);
    static bool WithdrawBalanceByAccId(std::string& accId,
                                       unsigned int withdraw_amount, int cusId);
    static void UpdateAccount(Account &targetAcc);
    static void DeleteAccount(std::string accId);
};