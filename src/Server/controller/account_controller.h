
#include "transaction_logdb.h"
#include "accountdb.h"

#include "savingsdb.h"
#include "customerdb.h"
#include "fixedDepositdb.h"

#include <vector>

class AccountController
{
public:
    static std::tuple<bool, std::string> CreateFixedDepositAccount(std::string userId, double interestRate, unsigned long long monthly_payment, std::string duedate);
    static std::tuple<bool, std::string> CreateNormalSavingsAccount(std::string userId, double interestRate);
    static Account GetAccountByAccNum(std::string accNum);
    static std::vector<TransactionLog> GetAccountLogs(std::string accNum);
    static std::vector<Account> GetAccountsByUserId(std::string userId);
private:
};
