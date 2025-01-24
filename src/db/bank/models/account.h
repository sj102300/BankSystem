#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include "customer.h"

struct Account {
    int accId;
    int cusId;
    int balance;
    int account_type;
    bool status;
    std::string created_at;

    static auto getTableDefinition() {
        return sqlite_orm::make_table("Account",
            sqlite_orm::make_column("accId", &Account::accId, sqlite_orm::primary_key()),
            sqlite_orm::make_column("cusId", &Account::cusId),
            sqlite_orm::make_column("balance", &Account::balance),
            sqlite_orm::make_column("account_type", &Account::account_type),
            sqlite_orm::make_column("status", &Account::status),
            sqlite_orm::make_column("created_at", &Account::created_at),
            sqlite_orm::foreign_key(&Account::cusId).references(&Customer::cusId));
    }
};
