
#include "savings.h"

class NormalSavings : public Savings{
protected:
    NormalSavings(account::AccountInfo ainfo, account::SavingsInfo sinfo): Savings(ainfo, sinfo) {}
public:
    virtual void withdraw() = 0;
};

class NormalSavingsImpl : public NormalSavings{
public:
    NormalSavingsImpl(account::AccountInfo ainfo, account::SavingsInfo sinfo): NormalSavings(ainfo, sinfo) {}

    void close_account() override;
    void deposit() override;
    void calcInterestRate() override;
    void withdraw() override;
};