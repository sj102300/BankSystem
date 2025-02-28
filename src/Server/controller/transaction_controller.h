
#include "models/Log/logging_namespace.h"
#include "accountdb.h"
#include "savingsdb.h"

class TransactionController
{
public:
    static std::tuple<bool, std::string> Transfer(std::string accDest, std::string accSrc, unsigned long long amount);
    static void Deposit();
    static void Withdraw();
private:
    static void MakeTransferLog(unsigned long long trade_amount, Account& destAcc, Savings& destSavings, Account& srcAcc, Savings& srcSavings);
};