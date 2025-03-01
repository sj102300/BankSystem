
#include "account_controller.h"
#include "savingsdb.h"
#include "customerdb.h"
#include "fixedDepositdb.h"

std::tuple<bool, std::string> AccountController::CreateFixedDepositAccount(std::string userId, double interestRate, unsigned long long monthly_payment, std::string duedate)
{
    Account newAcc = AccountDB::CreateAccount(userId, account::FIXED_DEPOSIT);
    Savings newSavings = SavingsDB::CreateSavings(newAcc.accNum, interestRate);
    FixedDeposit newFixedDeposit = FixedDepositDB::CreateFixedDeposit(newAcc.accNum, monthly_payment, duedate);
    
    // account::FixedDepositImplInfo ret = {
    //     {newAcc.accNum, userId, newAcc.account_type, newAcc.status, newAcc.created_at},
    //     {newSavings.balance, newSavings.interestRate},
    //     {newFixedDeposit.monthlyPayment, newFixedDeposit.duedate}};
    return {true, newAcc.accNum};
}

std::tuple<bool, std::string> AccountController::CreateNormalSavingsAccount(std::string userId, double interestRate)
{
    Account newAcc = AccountDB::CreateAccount(userId, account::NORMAL_SAVINGS);
    Savings newSavings = SavingsDB::CreateSavings(newAcc.accNum, interestRate);

    // account::NormalSavingsImplInfo ret = {
    //     {newAcc.accNum, userId, newAcc.account_type, newAcc.status, newAcc.created_at},
    //     {newSavings.balance, newSavings.interestRate}};

    return {true, newAcc.accNum};
}

Account AccountController::GetAccountByAccNum(std::string accNum){
    const auto [isAvailable, acc] = AccountDB::GetAccountByAccNum(accNum);
    return acc;
}


std::vector<TransactionLog> AccountController::GetAccountLogs(std::string accNum)
{
    return TransactionLogDB::GetTransactionLogsByaccNum(accNum);
}

std::vector<Account> AccountController::GetAccountsByUserId(std::string userId)
{
    Customer cus;
    bool result;
    std::tie(result, cus) = CustomerDB::GetCustomerByUserId(userId);
    if (!result)
    {
        // 유저 조회 실패 - 빈백터 반환
        return {};
    }

    return AccountDB::GetAccountsByUserId(userId);
}