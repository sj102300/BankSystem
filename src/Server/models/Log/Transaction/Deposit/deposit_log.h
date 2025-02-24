
#include "transaction.h"

class DepositLog: public Transaction{
public:
    DepositLog(log::LogInfo linfo, log::TransactionInfo tinfo): Transaction(linfo, tinfo) {}
    
    void make_log() override;
};