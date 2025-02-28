
#include "transaction.h"

class TransferLog: public Transaction{
public:
    TransferLog(logging::LogInfo linfo, logging::TransactionInfo tinfo): Transaction(linfo, tinfo) {}
    
    void make_log() override;
};