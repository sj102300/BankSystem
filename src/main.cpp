// #include "BankSystem/account.h"
#include "BankSystem/atm.h"
#include "bank_database.h"

// #include "bank/models/accountdb.h"
// #include "bank/models/customerdb.h"

int main(void)
{
    // ATM을 client로 나머지를 server로
    BankDatabase *db = BankDatabase::getInstance();
    db->initStorage();

    BankSystem::ATM atm1;
    atm1.Welcome();

    return 0;
}