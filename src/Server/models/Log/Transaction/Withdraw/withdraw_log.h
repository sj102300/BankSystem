
#include "transaction.h"

class WithdrawLog: public Transaction{
public:
    WithdrawLog(log::LogInfo linfo, log::TransactionInfo tinfo): Transaction(linfo, tinfo) {}
    
    void make_log() override;
};