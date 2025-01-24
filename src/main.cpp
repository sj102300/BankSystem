#include "BankSystem/account.h"
#include "BankSystem/atm.h"
#include "bank/bank_database.h"
#include "bank/models/customer.h"

int main(void) {
  BankSystem::Customer cus1("LEE");

  BankSystem::ATM atm;
  atm.CustomerVisit(cus1);

  return 0;
}