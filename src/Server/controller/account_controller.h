
#include "models/Account/account_namespace.h"
#include "transaction_logdb.h"
#include "accountdb.h"
#include <vector>

class AccountController
{
public:
    static account::FixedDepositImplInfo CreateFixedDepositAccount(std::string userId, double interestRate, unsigned long long monthly_payment, std::string duedate);
    static account::NormalSavingsImplInfo CreateNormalSavingsAccount(std::string userId, double interestRate);
    static std::vector<TransactionLog> GetAccountLogs(std::string accNum);
    static std::vector<Account> GetAccountsByUserId(std::string userId);
private:
};
