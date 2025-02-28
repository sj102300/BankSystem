
#include <string>

namespace account{
    enum{
        FIXED_DEPOSIT = 1, NORMAL_SAVINGS, 
    };

    typedef struct _accountInfo{
        const unsigned int accId_;
        const std::string accNum_; //계좌번호
        const unsigned int cusId_; 
        const unsigned int accountType_;
        bool status_;
        const std::string createdAt_;
    } AccountInfo;

    typedef struct _savingsInfo{
        long long balance_;
        double interestRate_;
    } SavingsInfo;

    typedef struct _fixedDepositInfo{
        unsigned long long monthlyPayment_;
        std::string maturityDate_;
    } FixedDepositInfo;

    typedef struct _fixedDepositImplInfo{
        AccountInfo ainfo;
        SavingsInfo sinfo;
        FixedDepositInfo finfo;
    } FixedDepositImplInfo;

    typedef struct _normalSavingsImplInfo{
        AccountInfo ainfo;
        SavingsInfo sinfo;
    } NormalSavingsImplInfo;
}