
#include "transaction.h"

class DepositLog: public Transaction{
public:
    DepositLog(logging::LogInfo linfo, logging::TransactionInfo tinfo): Transaction(linfo, tinfo) {}
    
    void make_log() override;
};