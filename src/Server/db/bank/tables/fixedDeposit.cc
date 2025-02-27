
#include "fixedDeposit.h"
#include "bank_database.h"

FixedDepositDB::FixedDepositDB() {}

FixedDeposit FixedDepositDB::CreateFixedDeposit(unsigned int accId, unsigned long long monthly_payment, std::string duedate){
    BankDatabase *db = BankDatabase::getInstance();

    int insertedId = db->getStorage().insert(FixedDeposit{
        accId,
        monthly_payment,
        duedate
    });

    FixedDeposit insertedFixedDeposit = db->getStorage().get<FixedDeposit>(insertedId);
    return insertedFixedDeposit;
}

std::tuple<bool, FixedDeposit> FixedDepositDB::GetFixedDeposit(unsigned int accId){
    BankDatabase *db = BankDatabase::getInstance();

    std::vector<FixedDeposit> ret = db->getStorage().get_all<FixedDeposit>(where(c(&FixedDeposit::accId) == accId));

    if(ret.empty())
        return {false, {}};

    return {true, ret.at(0)};
}

void FixedDepositDB::UpdateFixedDeposit(){
    
}

void FixedDepositDB::DeleteFixedDeposit(){

}