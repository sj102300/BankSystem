
#include "fixedDepositdb.h"
#include "bank_database.h"

FixedDepositDB::FixedDepositDB() {}

FixedDeposit FixedDepositDB::CreateFixedDeposit(std::string accNum, unsigned long long monthly_payment, std::string duedate){
    BankDatabase *db = BankDatabase::getInstance();

    int insertedId = db->getStorage().insert(FixedDeposit{
        accNum,
        monthly_payment,
        duedate
    });

    FixedDeposit insertedFixedDeposit = db->getStorage().get<FixedDeposit>(insertedId);
    return insertedFixedDeposit;
}

std::tuple<bool, FixedDeposit> FixedDepositDB::GetFixedDepositInfo(std::string accNum){
    BankDatabase *db = BankDatabase::getInstance();

    std::vector<FixedDeposit> ret = db->getStorage().get_all<FixedDeposit>(where(c(&FixedDeposit::accNum) == accNum));

    if(ret.empty())
        return {false, {}};

    return {true, ret.at(0)};
}

std::tuple<bool, account::FixedDepositImplInfo> FixedDepositDB::GetFixedDepositImpl(std::string accNum){
    BankDatabase *db = BankDatabase::getInstance();

    /*
        unsigned int accId;          // 자동 증가 primary key
    std::string accNum; // 12자리 계좌번호
    std::string userId;
    unsigned int account_type;
    bool status;
    std::string created_at;
    */

    auto joined_data = db->getStorage().select(
        columns(&Account::accNum, &Account::userId, &Account::account_type, &Account::status, &Account::created_at,
            &Savings::balance, &Savings::interestRate, 
            &FixedDeposit::duedate, &FixedDeposit::monthlyPayment),
        join<Savings>(on(c(&Account::accNum) == &Savings::accNum)),
        join<FixedDeposit>(on(c(&Account::accNum) == &FixedDeposit::accNum)));
    
    // vector.()
    return {true, {}};
}


void FixedDepositDB::UpdateFixedDeposit(){
    
}

void FixedDepositDB::DeleteFixedDeposit(){

}