
#include <string>

namespace account{
    enum{
        FIXED_DEPOSIT = 1, NORMAL_SAVINGS, 
    };

    typedef struct _accountInfo{
        const std::string accNum; //계좌번호
        const std::string userId;
        const unsigned int account_type;
        const bool status;
    } AccountInfo;

    typedef struct _savingsInfo{
        long long balance;
        double interestRate;
    } SavingsInfo;

    typedef struct _fixedDepositInfo{
        unsigned long long monthlyPayment;
        std::string maturityDate;
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