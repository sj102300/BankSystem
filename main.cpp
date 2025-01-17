#include <iostream>

#include "atm.h"
#include "customer.h"
#include "account.h"

int main(void) {
    BankSystem::Customer cus1("LEE");
    
    BankSystem::ATM atm;
    atm.CustomerVisit(cus1);

    return 0;
}