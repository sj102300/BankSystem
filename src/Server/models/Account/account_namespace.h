
#include <string>

namespace account{
    typedef struct _accountInfo{
        const unsigned int accId_;
        const std::string accNum_; //계좌번호
        const unsigned int cusId_;
        bool status_;
        const unsigned int accountType_;
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
}