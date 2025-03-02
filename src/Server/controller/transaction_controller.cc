
#include "transaction_controller.h"
#include "transaction_logdb.h"
#include "get_current_time.h"
#include "logging_namespace.h"

std::tuple<bool, std::string> TransactionController::Transfer(std::string destAccNum, std::string srcAccNum, unsigned long long amount)
{

    const auto [isAvailableDestAcc, destAcc] = AccountDB::GetAccountByAccNum(destAccNum);
    if (!isAvailableDestAcc)
        return {false, "destination 계좌 조회 실패"};
    const auto [isAvailableSrcAcc, srcAcc] = AccountDB::GetAccountByAccNum(srcAccNum);
    if (!isAvailableSrcAcc)
        return {false, "src 계좌 조회 실패"};

    const auto [isAvailableDestSavings, destSavings] = SavingsDB::GetSavings(destAcc.accNum);
    if (!isAvailableDestSavings)
        return {false, "destination 계좌 조회 실패"};
    const auto [isAvailableSrcSavings, srcSavings] = SavingsDB::GetSavings(srcAcc.accNum);
    if (!isAvailableSrcSavings)
        return {false, "src 계좌 조회 실패"};

    if (srcSavings.balance < amount)
        return {false, "계좌 잔액 부족"};

    SavingsDB::UpdateSavingsBalance(destAcc.accNum, destSavings.balance + amount);
    SavingsDB::UpdateSavingsBalance(srcAcc.accNum, srcSavings.balance - amount);

    unsigned int srcTransferLogId = MakeTransferLog(amount, destAccNum, srcAccNum, srcAcc.userId);

    return {true, std::to_string(srcTransferLogId)};
}

void TransactionController::Deposit()
{
}

void TransactionController::Withdraw()
{
}

TransactionLog TransactionController::GetLogByLogId(unsigned int logId){
    return TransactionLogDB::GetTransactionLogByLogId(logId);
}


//보낸쪽의 송금 로그 id 반환환
unsigned int TransactionController::MakeTransferLog(unsigned long long trade_amount, std::string destAccNum, std::string srcAccNum,
                                            std::string srcUserId)
{
    std::string createdAt = TimeStamp::get_current_time();

    const auto [isAvailableDestSavings, destSavings] = SavingsDB::GetSavings(destAccNum);
    const auto [isAvailableSrcSavings, srcSavings] = SavingsDB::GetSavings(srcAccNum);

    TransactionLogDB::CreateTransactionLog(destAccNum, srcUserId, logging::TRANSFER_DEST, trade_amount, destSavings.balance);
    TransactionLog log = TransactionLogDB::CreateTransactionLog(srcAccNum, srcUserId, logging::TRANSFER_SRC, trade_amount, srcSavings.balance);

    return log.logId;
}