
#include "transaction.h"

class WithdrawLog: public Transaction{
public:
    WithdrawLog(logging::LogInfo linfo, logging::TransactionInfo tinfo): Transaction(linfo, tinfo) {}
    
    void make_log() override;
};