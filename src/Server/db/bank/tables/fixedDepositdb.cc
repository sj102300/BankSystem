
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

std::tuple<bool, FixedDeposit> FixedDepositDB::GetFixedDeposit(std::string accNum){
    BankDatabase *db = BankDatabase::getInstance();

    std::vector<FixedDeposit> ret = db->getStorage().get_all<FixedDeposit>(where(c(&FixedDeposit::accNum) == accNum));

    if(ret.empty())
        return {false, {}};

    return {true, ret.at(0)};
}

void FixedDepositDB::UpdateFixedDeposit(){
    
}

void FixedDepositDB::DeleteFixedDeposit(){

}