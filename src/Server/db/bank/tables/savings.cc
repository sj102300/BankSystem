
#include "savings.h"
#include "bank_database.h"

SavingsDB::SavingsDB() {}

Savings SavingsDB::CreateSavings(unsigned int accId, long long balance, double interestRate){
    BankDatabase *db = BankDatabase::getInstance();
    
    int insertedId = db->getStorage().insert(Savings{
        accId,
        balance,
        interestRate
    });

    Savings insertedSavings = db->getStorage().get<Savings>(insertedId);
    return insertedSavings;
}

std::tuple<bool, Savings> SavingsDB::GetSavings(unsigned int accId){
    BankDatabase *db = BankDatabase::getInstance();

    std::vector<Savings> ret = db->getStorage().get_all<Savings>(where(c(&Savings::accId) == accId));

    if(ret.empty())
        return {false, {}};

    return {true, ret.at(0)};
}

void SavingsDB::UpdateSavings(){

}

void SavingsDB::DeleteSavings(){

}