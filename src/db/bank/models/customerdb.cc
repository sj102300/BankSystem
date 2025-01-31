#include "bank_database.h"
#include <string>

void CustomerDB::CreateCustomer(std::string& name) {
    try {
        db->getStorage().insert(Customer{0, name});
    } catch (std::exception& e) {
        db->handleException(e);
    }
}

bool CustomerDB::isExistByCusId(int cusId) {
    try {
        return db->getStorage().count<Customer>(where(c(&Customer::cusId) == cusId));
    } catch (std::exception& e) {
        db->handleException(e);
    }
}

std::string& CustomerDB::GetCustomerName(int cusId) {
    try {
        Customer targetCus = db->getStorage().get<Customer>(where(c(&Customer::cusId) == cusId));
        return targetCus.cus_name;
    } catch (std::exception& e) {
        db->handleException(e);
    }
}

void CustomerDB::UpdateCustomer(int cusId, std::string& changing_name) {
    try {
        db->getStorage().update_all(set(c(&Customer::cus_name) = changing_name), where(c(&Customer::cusId) == cusId));
    } catch (std::exception& e) {
        db->handleException(e);
    }
}

void CustomerDB::DeleteCustomer(int cusId) {
    // 고객에 딸린 account status false로
    // db에서 없애진 말자 transactionlog가 외래키로 잡혀있어서..
}
