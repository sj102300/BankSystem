#pragma once

#include <sqlite_orm/sqlite_orm.h>

using namespace sqlite_orm;

namespace db_table{
    struct Customer{
        unsigned int cusId;
        std::string userId;
        std::string password;
        std::string name;
        std::string createdAt;

        static auto getTableDefinition(){
            return make_table(
                "Customer",
                make_column("cusId", &Customer::cusId, primary_key().autoincrement()),
                make_column("userId", &Customer::userId, unique()),
                make_column("password", &Customer::password),
                make_column("name", &Customer::name),
                make_column("createdAt", &Customer::createdAt)
            );
        }
    };

    struct Account{
        unsigned int accId;     //자동증가 primary key
        std::string accNum;     //계좌번호
        unsigned int cusId; 
        bool status;
        unsigned int accountType; 
        std::string createdAt;

        static auto getTableDefinition(){
            return make_table(
                "Account",
                make_column("accId", &Account::accId, primary_key().autoincrement()),
                make_column("accNum", &Account::accNum, unique(), check(length(&Account::accNum) == 12)),
                make_column("cusId", &Account::cusId),
                make_column("status", &Account::status, default_value(true)),
                make_column("accountType", &Account::accountType),
                make_column("createdAt", &Account::createdAt),
                foreign_key(&Account::cusId).references(&Customer::cusId)
            );
        }
    };

    struct Savings{
        unsigned int accId;
        long long balance;
        double interestRate;

        static auto getTableDefinition(){
            return make_table(
                "Savings",
                make_column("accId", &Savings::accId, primary_key().autoincrement()),
                make_column("balance", &Savings::balance, default_value(0)),
                make_column("interestRate", &Savings::interestRate, default_value(0)),
                foreign_key(&Savings::accId).references(&Account::accId)
            );
        }
    };

    struct FixedDeposit{
        unsigned int accId;
        unsigned long long monthlyPayment;
        std::string duedate;

        static auto getTableDefinition(){
            return make_table(
                "FixedDeposit",
                make_column("accId", &FixedDeposit::accId, primary_key().autoincrement()),
                make_column("monthlyPayment", &FixedDeposit::monthlyPayment),
                make_column("duedate", &FixedDeposit::duedate),
                foreign_key(&FixedDeposit::accId).references(&Account::accId)
            );
        }
    };

    struct TransactionLog{
        unsigned int logId;
        unsigned int cusId;
        std::string createdAt;
        std::string accNum;
        long long remainingBalance;
        long long tradeAmount;
        unsigned int logType;

        static auto getTableDefinition(){
            return make_table(
                "TransactionLog",
                make_column("logId", &TransactionLog::logId, primary_key().autoincrement()),
                make_column("cusId", &TransactionLog::cusId),
                make_column("createdAt", &TransactionLog::createdAt),
                make_column("accNum", &TransactionLog::accNum),
                make_column("remainingBalance", &TransactionLog::remainingBalance),
                make_column("tradeAmount", &TransactionLog::tradeAmount),
                make_column("logType", &TransactionLog::logType),
                foreign_key(&TransactionLog::accNum).references(&Account::accNum),
                foreign_key(&TransactionLog::cusId).references(&Account::cusId)
            );
        }
    };
}
