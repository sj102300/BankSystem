#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include "customer.h"
#include "account.h"

struct TransactionLog {
    int logId;
    int accId;
    int cusId;
    int transaction_type;
    int trade_amount;
    int remaining_balance;
    std::string created_at;

    static auto getTableDefinition() {
        return sqlite_orm::make_table("TransactionLog",
            sqlite_orm::make_column("logId", &TransactionLog::logId, sqlite_orm::primary_key()),
            sqlite_orm::make_column("accId", &TransactionLog::accId),
            sqlite_orm::make_column("cusId", &TransactionLog::cusId),
            sqlite_orm::make_column("transaction_type", &TransactionLog::transaction_type),
            sqlite_orm::make_column("trade_amount", &TransactionLog::trade_amount),
            sqlite_orm::make_column("remaining_balance", &TransactionLog::remaining_balance),
            sqlite_orm::make_column("created_at", &TransactionLog::created_at),
            sqlite_orm::foreign_key(&TransactionLog::accId).references(&Account::accId),
            sqlite_orm::foreign_key(&TransactionLog::cusId).references(&Customer::cusId));
    }
};
