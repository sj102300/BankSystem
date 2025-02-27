
#include <string>

namespace log{
    enum{
        DEPOSIT = 1, WITHDRAW, TRANSFER_DEST, TRANSFER_SRC
    };

    typedef struct _logInfo{
        const unsigned int logId; //db auto increment
        const unsigned int logType;
        const std::string createdAt;
    } LogInfo;

    typedef struct _transactionInfo{
        const std::string accId;
        const std::string userId; //로그인때 보여주는 아이디? 아니면 db autoincrement?
        const long long tradeAmount;
        const long long remainingBalance;
    } TransactionInfo;
}