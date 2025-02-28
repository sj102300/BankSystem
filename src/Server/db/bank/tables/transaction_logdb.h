#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include "customerdb.h"
#include "accountdb.h"

using namespace sqlite_orm;

struct TransactionLog
{
    unsigned int logId;     //auto increment. pk
    unsigned int accId;     // Account 테이블의 id를 참조
    unsigned int cusId;     // Customer 테이블의 id를 참조. 돈 보낸 사람
    std::string accNum; // 12자리 계좌번호 (조회용)
    unsigned int transaction_type; // 입금시 1, 송금시 2, 출금시 3
    unsigned long long trade_amount;
    unsigned long long remaining_balance;
    std::string created_at;

    static auto getTableDefinition()
    {
        return make_table(
            "TransactionLog",
            make_column("logId", &TransactionLog::logId, primary_key().autoincrement()),
            make_column("accId", &TransactionLog::accId),
            make_column("cusId", &TransactionLog::cusId),
            make_column("accNum", &TransactionLog::accNum),
            make_column("transactionType", &TransactionLog::transaction_type),
            make_column("tradeAmount", &TransactionLog::trade_amount),
            make_column("remainingBalance", &TransactionLog::remaining_balance),
            make_column("createdAt", &TransactionLog::created_at),
            foreign_key(&TransactionLog::accNum).references(&Account::accNum),
            foreign_key(&TransactionLog::cusId).references(&Customer::cusId));
    }
};

class TransactionLogDB{
public:
    static TransactionLog CreateTransactionLog(TransactionLog info);
    static std::vector<TransactionLog> GetTransactionLogsByaccNum(std::string accNum);
};