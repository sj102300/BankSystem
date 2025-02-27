
#include "account_namespace.h"
#include <random>

class Account{
protected:
    //get method
    std::string getAccountNum(){ return info_.accNum_; }
    unsigned int getCusId() { return info_.cusId_; }
    bool getStatus() { return info_.status_; }
    unsigned int getAccountType() { return info_.accountType_; }
    std::string getCreatedAt() {return info_.createdAt_; }

    //set method
    void setStatus(bool status) { info_.status_ = status; }

    Account(account::AccountInfo info) :info_(info) {}
    
private: 
    account::AccountInfo info_;

public:
    virtual void closeAccount() = 0;
};