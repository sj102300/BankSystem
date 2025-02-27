
#include "transaction.h"

class TransferLog: public Transaction{
public:
    TransferLog(log::LogInfo linfo, log::TransactionInfo tinfo): Transaction(linfo, tinfo) {}
    
    void make_log() override;
};