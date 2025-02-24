
#include "account.h"

class Savings : public Account{
protected:
    //get method
    long long getBalance() { return info_.balance_; }
    double getInterestRate() { return info_.interestRate_; }

    //set method
    void setBalance(long long balance) { info_.balance_ = balance; }
    void setInterestRate(double interestRate) { info_.interestRate_ = interestRate; }

    Savings(account::AccountInfo ainfo, account::SavingsInfo sInfo) : Account(ainfo), info_(sInfo) {}

private:
    account::SavingsInfo info_;
public:
    virtual void deposit() = 0;
    virtual void calcInterestRate() =0;
};