
#include "logging.h"

class Transaction : public Log{
protected:
    Transaction(logging::LogInfo linfo, logging::TransactionInfo tinfo): Log(linfo), info_(tinfo) {}

private:
    const logging::TransactionInfo info_;
};