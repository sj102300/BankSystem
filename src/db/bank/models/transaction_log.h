#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include "customer.h"
#include "account.h"

using namespace sqlite_orm;

struct TransactionLog {
    int logId;
    int accountId;  // Account 테이블의 id를 참조
    std::string accId;  // 12자리 계좌번호 (조회용)
    int cusId;
    int transaction_type;
    int trade_amount;
    int remaining_balance;
    std::string created_at;

    static auto getTableDefinition() {
        return make_table("TransactionLog",
            make_column("logId", &TransactionLog::logId, primary_key()),
            make_column("accountId", &TransactionLog::accountId),
            make_column("accId", &TransactionLog::accId),
            make_column("cusId", &TransactionLog::cusId),
            make_column("transaction_type", &TransactionLog::transaction_type),
            make_column("trade_amount", &TransactionLog::trade_amount),
            make_column("remaining_balance", &TransactionLog::remaining_balance),
            make_column("created_at", &TransactionLog::created_at),
            foreign_key(&TransactionLog::accountId).references(&Account::id),
            foreign_key(&TransactionLog::cusId).references(&Customer::cusId));
    }
};
