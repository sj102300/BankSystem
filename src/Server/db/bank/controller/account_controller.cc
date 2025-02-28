
#include "account_controller.h"  //같은 폴더내에 있는 account.h
#include "savingsdb.h"
#include "fixedDepositdb.h"

account::FixedDepositImplInfo AccountController::CreateFixedDepositAccount(unsigned int cusId, double interestRate, unsigned long long monthly_payment, std::string duedate){
    Account newAcc = AccountDB::CreateAccount(cusId, account::FIXED_DEPOSIT);
    Savings newSavings = SavingsDB::CreateSavings(newAcc.accId, interestRate);
    FixedDeposit newFixedDeposit = FixedDepositDB::CreateFixedDeposit(newAcc.accId, monthly_payment, duedate);

    account::FixedDepositImplInfo ret = {
        {newAcc.accId, newAcc.accNum, newAcc.cusId, newAcc.account_type, newAcc.status, newAcc.created_at},
        {newSavings.balance, newSavings.interestRate},
        {newFixedDeposit.monthlyPayment, newFixedDeposit.duedate}
    };
    return ret;
}

account::NormalSavingsImplInfo AccountController::CreateNormalSavingsAccount(unsigned int cusId, double interestRate){
    Account newAcc = AccountDB::CreateAccount(cusId, account::NORMAL_SAVINGS);
    Savings newSavings = SavingsDB::CreateSavings(newAcc.accId, interestRate);
    
    account::NormalSavingsImplInfo ret = {
        {newAcc.accId, newAcc.accNum, newAcc.cusId, newAcc.account_type, newAcc.status, newAcc.created_at},
        {newSavings.balance, newSavings.interestRate}
    };

    return ret;
}

std::vector<TransactionLog> AccountController::GetAccountLogs(std::string accNum){
    return TransactionLogDB::GetTransactionLogsByaccNum(accNum);
}

std::vector<Account> AccountController::GetAccountsByUserId(std::string userId){
    Customer cus;
    bool result;
    std::tie(result, cus) = CustomerDB::GetCustomerByUserId(userId);
    if(!result){
        //유저 조회 실패 - 빈백터 반환
        return {}; 
    }
    
    return AccountDB::GetAccountsByCusId(cus.cusId);
}