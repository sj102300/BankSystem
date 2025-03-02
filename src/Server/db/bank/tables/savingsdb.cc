
#include "savingsdb.h"
#include "bank_database.h"

SavingsDB::SavingsDB() {}

Savings SavingsDB::CreateSavings(std::string userId, double interestRate)
{
    BankDatabase *db = BankDatabase::getInstance();

    int insertedId = db->getStorage().insert(Savings{
        0,
        userId,
        0,
        interestRate});

    Savings insertedSavings = db->getStorage().get<Savings>(insertedId);
    return insertedSavings;
}

std::tuple<bool, Savings> SavingsDB::GetSavings(std::string accNum)
{
    BankDatabase *db = BankDatabase::getInstance();

    std::vector<Savings> ret = db->getStorage().get_all<Savings>(where(c(&Savings::accNum) == accNum));

    if (ret.empty())
        return {false, Savings{}};

    return {true, ret.at(0)};
}

void SavingsDB::UpdateSavingsBalance(std::string accNum, unsigned long long changedBalance)
{
    BankDatabase *db = BankDatabase::getInstance();

    db->getStorage().update_all(set(c(&Savings::balance) = changedBalance),
                                where(c(&Savings::accNum) == accNum));
}

void SavingsDB::UpdateSavings(Savings &savings)
{
    BankDatabase *db = BankDatabase::getInstance();
    db->getStorage().update(savings);
}

void SavingsDB::DeleteSavings()
{
}