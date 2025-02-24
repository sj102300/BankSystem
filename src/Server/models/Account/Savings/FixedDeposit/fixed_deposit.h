
#include "savings.h"
#include <string>

class FixedDeposit: public Savings{

protected:
    //get method
    unsigned long long get_monthlyPayment() { return info_.monthlyPayment_; }
    std::string get_maturityDate() { return info_.maturityDate_; }

    //set method
    void setMonthlyPayment(unsigned long long monthlyPayment){ info_.monthlyPayment_ = monthlyPayment; }
    void setMaturityDate(std::string maturityDate) { info_.maturityDate_ = maturityDate; }

    FixedDeposit(account::AccountInfo ainfo, account::SavingsInfo sInfo, account::FixedDepositInfo fInfo)
        :Savings(ainfo, sInfo) , info_(fInfo) {}

private:
    account::FixedDepositInfo info_;

public:
    virtual bool checkMaturityDate() = 0;
    // virtual void cancelEarly() = 0; 
    // virtual void finalizeMaturity() = 0;
};

namespace{
    std::string get_account_num(){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<unsigned long long> distrib(100000000000, 999999999999);
        return std::to_string(distrib(gen));
    }
}

//구현 클래스
class FixedDepositImpl: public FixedDeposit{
public:
    void close_account() override;
    void deposit() override;
    void calcInterestRate() override;
    bool checkMaturityDate() override;
};