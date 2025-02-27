
#include "transaction_logdb.h"
#include "bank_database.h"
#include "get_current_time.h"

TransactionLog TransactionLogDB::CreateTransactionLog(TransactionLog info){
    BankDatabase *db = BankDatabase::getInstance();

    info.created_at = TimeStamp::get_current_time();
    
    int insertedId = db->getStorage().insert(info);

    TransactionLog insertedLog = db->getStorage().get<TransactionLog>(insertedId);
    return insertedLog;
}

std::vector<TransactionLog> TransactionLogDB::GetTransactionLogsByaccNum(std::string accNum){
    BankDatabase *db = BankDatabase::getInstance();

    std::vector<TransactionLog> ret = db->getStorage().get_all<TransactionLog>(where(c(&TransactionLog::accNum) == accNum));
    return ret;
}