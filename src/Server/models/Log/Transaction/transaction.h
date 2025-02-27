
#include "log.h"

class Transaction : public Log{
protected:
    Transaction(log::LogInfo linfo, log::TransactionInfo tinfo): Log(linfo), info_(tinfo) {}

private:
    const log::TransactionInfo info_;
};