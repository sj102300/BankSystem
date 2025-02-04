#include "BankSystem/atm.h"
#include "bank_database.h"

int main(void)
{
    //db연동
    BankDatabase *db = BankDatabase::getInstance();
    db->initStorage();

    //client시작
    BankSystem::ATM::Welcome();

    return 0;
}