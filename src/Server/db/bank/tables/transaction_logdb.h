#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include "customerdb.h"
#include "accountdb.h"

using namespace sqlite_orm;

struct TransactionLog
{
    unsigned int logId;
    unsigned int accId;     // Account 테이블의 id를 참조
    unsigned int cusId;     // Customer 테이블의 id를 참조
    std::string accNum; // 12자리 계좌번호 (조회용)
    unsigned int transaction_type; // 입금시 1, 송금시 2, 출금시 3
    unsigned int trade_amount;
    unsigned int remaining_balance;
    std::string created_at;
    unsigned int logType;

    static auto getTableDefinition()
    {
        return make_table(
            "TransactionLog",
            make_column("logId", &TransactionLog::logId, primary_key().autoincrement()),
            make_column("cusId", &TransactionLog::cusId),
            make_column("createdAt", &TransactionLog::created_at),
            make_column("accNum", &TransactionLog::accNum),
            make_column("remainingBalance", &TransactionLog::remaining_balance),
            make_column("tradeAmount", &TransactionLog::trade_amount),
            make_column("logType", &TransactionLog::logType),
            foreign_key(&TransactionLog::accNum).references(&Account::accNum),
            foreign_key(&TransactionLog::cusId).references(&Account::cusId));
    }
};
