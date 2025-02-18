#include <string>
#include <tuple>

#include "bank_database.h"

CustomerDB::CustomerDB() {}

Customer CustomerDB::CreateCustomer(std::string &name)
{
    BankDatabase *db = BankDatabase::getInstance();
    int insertedId = db->getStorage().insert(Customer{0, name});
    Customer insertedCustomer = db->getStorage().get<Customer>(insertedId);
    return insertedCustomer;
}

bool CustomerDB::isExistByCusId(int cusId)
{
    BankDatabase *db = BankDatabase::getInstance();
    auto customer = db->getStorage().get_all<Customer>(where(c(&Customer::cusId) == cusId));
    if (customer.empty())
        return false; // 해당아이디의 고객 정보 없음.
    return true;
}

std::tuple<bool, const Customer> CustomerDB::GetCustomer(int cusId)
{
    BankDatabase *db = BankDatabase::getInstance();
    auto customer = db->getStorage().get_all<Customer>(where(c(&Customer::cusId) == cusId));
    if (customer.empty())
        return {false, {0, "\0"}}; // 고객 조회 실패.
    return {true, customer[0]};
}

std::tuple<bool, const Customer> CustomerDB::GetCustomer(std::string &name)
{
    BankDatabase *db = BankDatabase::getInstance();
    auto customer = db->getStorage().get_all<Customer>(where(c(&Customer::cus_name) == name));
    if (customer.empty())
        return {false, {0, "\0"}}; // 고객 조회 실패.
    return {true, customer[0]};
}

void CustomerDB::UpdateCustomer(int cusId, std::string &changing_name)
{
    BankDatabase *db = BankDatabase::getInstance();
    db->getStorage().update_all(set(c(&Customer::cus_name) = changing_name),
                                where(c(&Customer::cusId) == cusId));
}

void CustomerDB::DeleteCustomer(int cusId)
{
    // db에서 없애진 말자 transactionlog가 외래키로 잡혀있어서..
    // 고객에 딸린 account status false로
    BankDatabase *db = BankDatabase::getInstance();
    std::vector<Account> accounts = AccountDB::GetAccountsByCusId(cusId);
    for (auto it = accounts.begin(); it != accounts.end(); ++it)
    {
        it->status = false;
    }
}
