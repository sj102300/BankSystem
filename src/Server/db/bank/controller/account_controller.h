
#include "models/Account/account_namespace.h"
#include <vector>

class AccountController
{
public:
    static account::FixedDepositImplInfo CreateFixedDepositAccount(unsigned int cusId, double interestRate, unsigned long long monthly_payment, std::string duedate);
    static account::NormalSavingsImplInfo CreateNormalSavingsAccount(unsigned int cusId, double interestRate);
    static std::vector<TransactionLog> GetAccountLogs(std::string accNum);
    static std::vector<Account> GetAccountsByUserId(std::string userId);
private:
};
