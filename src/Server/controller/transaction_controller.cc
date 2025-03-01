
#include "transaction_controller.h"
#include "transaction_logdb.h"
#include "get_current_time.h"

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

    MakeTransferLog(amount, destAccNum, srcAccNum, srcAcc.userId);

    return {true, "송금 성공"};
}

void TransactionController::Deposit()
{
}

void TransactionController::Withdraw()
{
}

void TransactionController::MakeTransferLog(unsigned long long trade_amount, std::string destAccNum, std::string srcAccNum,
                                            std::string srcUserId)
{
    std::string createdAt = TimeStamp::get_current_time();

    const auto [isAvailableDestSavings, destSavings] = SavingsDB::GetSavings(destAccNum);
    const auto [isAvailableSrcSavings, srcSavings] = SavingsDB::GetSavings(srcAccNum);

    TransactionLogDB::CreateTransactionLog(destAccNum, srcUserId, logging::TRANSFER_DEST, trade_amount, destSavings.balance);
    TransactionLogDB::CreateTransactionLog(srcAccNum, srcUserId, logging::TRANSFER_SRC, trade_amount, srcSavings.balance);

    return;
}