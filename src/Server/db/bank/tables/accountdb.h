#pragma once
#include <sqlite_orm/sqlite_orm.h>

#include <string>
#include "customerdb.h"
#include <tuple>

using namespace sqlite_orm;

class BankDatabase;

struct Account
{
    unsigned int accId;          // 자동 증가 primary key
    std::string accNum; // 12자리 계좌번호
    std::string userId;
    unsigned int account_type;
    bool status;
    std::string created_at;

    static auto getTableDefinition()
    {
        return make_table(
            "Account",
            make_column("accId", &Account::accId, primary_key().autoincrement()),
            make_column("accNum", &Account::accNum, unique(), check(length(&Account::accNum) == 12)),
            make_column("userId", &Account::userId),
            make_column("status", &Account::status, default_value(true)),
            make_column("accountType", &Account::account_type),
            make_column("createdAt", &Account::created_at),
            foreign_key(&Account::userId).references(&Customer::userId));
    }
};

class AccountDB
{
public:
    AccountDB();
    static bool isExistAccNum(std::string &accNum);
    static Account CreateAccount(std::string userId, unsigned int account_type);
    static std::vector<Account> GetAccountsByUserId(std::string userId);
    static std::tuple<bool, Account> GetAccountByAccNum(std::string accNum);
    static void UpdateAccount(Account &targetAcc);
    static void DeleteAccount(std::string accNum);
};