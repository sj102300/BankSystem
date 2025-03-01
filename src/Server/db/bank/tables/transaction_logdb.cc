
#include "transaction_logdb.h"
#include "bank_database.h"
#include "get_current_time.h"

TransactionLog TransactionLogDB::CreateTransactionLog(std::string accNum, std::string userId, unsigned int transaction_type,
                                                      unsigned long long trade_amount, unsigned long long remaining_balance)
{
    BankDatabase *db = BankDatabase::getInstance();

    int insertedId = db->getStorage().insert(TransactionLog{
        0,
        accNum,
        userId,
        transaction_type,
        trade_amount,
        remaining_balance,
        TimeStamp::get_current_time()});

    TransactionLog insertedLog = db->getStorage().get<TransactionLog>(insertedId);
    return insertedLog;
}

std::vector<TransactionLog> TransactionLogDB::GetTransactionLogsByaccNum(std::string accNum)
{
    BankDatabase *db = BankDatabase::getInstance();

    return db->getStorage().get_all<TransactionLog>(where(c(&TransactionLog::accNum) == accNum));
}