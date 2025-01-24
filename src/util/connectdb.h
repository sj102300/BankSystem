#include <iostream>
#include <sqlite_orm/sqlite_orm.h>
#include <string>
using namespace sqlite_orm;
using namespace std;

// 구조체 정의
typedef struct _customer {
    int cusId;              // 고객 ID
    std::string cus_name;   // 고객 이름
}Customer;

typedef struct _account {
    int accId;              // 계좌 ID
    int cusId;              // 고객 ID (외래 키)
    int balance;            // 잔액
    int account_type;       // 계좌 유형 (1: 일반계좌, 2: 주식계좌)
    bool status;            // 계좌 상태
    std::string created_at; // 계좌 개설 시간
}Account;

typedef struct _transactionLog {
    int logId;               // 로그 ID
    int accId;               // 계좌 ID (외래 키)
    int cusId;               // 고객 ID (외래 키)
    int transaction_type;    // 거래 유형 (1: 입금, 2: 출금)
    int trade_amount;        // 거래 금액
    int remaining_balance;   // 남은 잔액
    std::string created_at;  // 거래 시간
}TransactionLog;


// SQLite ORM을 사용하여 테이블 정의 및 매핑
auto initStorage(const string& db_path) {

    return make_storage(
        db_path,
        
        // Customer 테이블 매핑
        make_table("Customer",
                   make_column("cusId", &Customer::cusId, primary_key()),
                   make_column("cus_name", &Customer::cus_name)),
        
        // Account 테이블 매핑
        make_table("Account",
                   make_column("accId", &Account::accId, primary_key()),
                   make_column("cusId", &Account::cusId),
                   make_column("balance", &Account::balance),
                   make_column("account_type", &Account::account_type),
                   make_column("status", &Account::status),
                   make_column("created_at", &Account::created_at, default_value("CURRENT_TIMESTAMP")),
                   foreign_key(&Account::cusId).references(&Customer::cusId)),
        
        // TransactionLog 테이블 매핑
        make_table("TransactionLog",
                   make_column("logId", &TransactionLog::logId, primary_key()),
                   make_column("accId", &TransactionLog::accId),
                   make_column("cusId", &TransactionLog::cusId),
                   make_column("transaction_type", &TransactionLog::transaction_type),
                   make_column("trade_amount", &TransactionLog::trade_amount),
                   make_column("remaining_balance", &TransactionLog::remaining_balance),
                   make_column("created_at", &TransactionLog::created_at, default_value("CURRENT_TIMESTAMP")),
                   foreign_key(&TransactionLog::accId).references(&Account::accId),
                   foreign_key(&TransactionLog::cusId).references(&Customer::cusId))
    );
}
