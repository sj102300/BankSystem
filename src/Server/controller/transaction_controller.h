
#include "accountdb.h"
#include "savingsdb.h"
#include "transaction_logdb.h"

class TransactionController
{
public:
    static std::tuple<bool, std::string> Transfer(std::string accDest, std::string accSrc, unsigned long long amount);
    static void Deposit();
    static void Withdraw();
    static TransactionLog GetLogByLogId(unsigned int logId);

private:
    static unsigned int MakeTransferLog(unsigned long long trade_amount, std::string destAccNum, std::string srcAccNum, std::string srcUserId);
};