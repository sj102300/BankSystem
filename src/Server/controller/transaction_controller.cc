
#include "transaction_controller.h"
#include "transaction_logdb.h"
#include "get_current_time.h"

std::tuple<bool, std::string> TransactionController::Transfer(std::string destAccNum, std::string srcAccNum, unsigned long long amount){
    Account destAcc, srcAcc;
    bool isAvailable;
    std::tie(isAvailable, destAcc) = AccountDB::GetAccountByAccNum(destAccNum);
    if(isAvailable)
        return {false, "destination 계좌 조회 실패"};
    std::tie(isAvailable, srcAcc) = AccountDB::GetAccountByAccNum(srcAccNum);
    if(isAvailable)
        return {false, "src 계좌 조회 실패"};
    
    Savings destSavings, srcSavings;
    std::tie(isAvailable, destSavings) = SavingsDB::GetSavings(destAcc.accId);
    if(isAvailable)
        return {false, "destination 계좌 조회 실패"};
    std::tie(isAvailable, srcSavings) = SavingsDB::GetSavings(srcAcc.accId);
    if(isAvailable)
        return {false, "src 계좌 조회 실패"};

    if(srcSavings.balance < amount)
        return {false, "계좌 잔액 부족"};
    
    srcSavings.balance -= amount;
    destSavings.balance += amount;

    SavingsDB::UpdateSavings(destSavings);
    SavingsDB::UpdateSavings(srcSavings);

    MakeTransferLog(amount, destAcc, destSavings, srcAcc, srcSavings);

    return {true, "송금 성공"};
}

void TransactionController::Deposit(){

}

void TransactionController::Withdraw(){

}

void TransactionController::MakeTransferLog(unsigned long long trade_amount, Account& destAcc, Savings& destSavings, Account& srcAcc, Savings& srcSavings)
{
    std::string createdAt = TimeStamp::get_current_time();
    
    //받은쪽 로그
    TransactionLog destInfo = {
        0, destAcc.accId, srcAcc.cusId, destAcc.accNum, logging::TRANSFER_DEST, trade_amount, destSavings.balance, createdAt
    };
    TransactionLogDB::CreateTransactionLog(destInfo);
    
    //보낸쪽 로그
    TransactionLog srcInfo = {
        0, srcAcc.accId, srcAcc.cusId, srcAcc.accNum, logging::TRANSFER_SRC, trade_amount, srcSavings.balance, createdAt
    };
    TransactionLogDB::CreateTransactionLog(srcInfo);
    return;
}