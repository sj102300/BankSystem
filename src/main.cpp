#include "db/bank/bank_database.h"

int main(void)
{
    auto db = BankDatabase::getInstance();
    db->initStorage();

    return 0;
}