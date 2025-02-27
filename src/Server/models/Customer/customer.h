
#include "customer_namespace.h"

class Customer{
private:
    customer::CustomerInfo info_;

protected:
    Customer(customer::CustomerInfo info): info_(info) {}
    
    //get method
    std::string getUserId() { return info_.userId; }
    unsigned int getCusId() { return info_.cusId; }
    std::string getCusName() { return info_.name; }

    //set method
    void setCusName(std::string name) {info_.name = name; }

public:
    virtual bool login() = 0;
};