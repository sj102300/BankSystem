#include <string>
#include <tuple>

#include "bank_database.h"
#include "get_current_time.h"

CustomerDB::CustomerDB() {}

Customer CustomerDB::CreateCustomer(std::string userId, std::string password, std::string name)
{
    BankDatabase *db = BankDatabase::getInstance();
    std::string createdAt = TimeStamp::get_current_time();
    int insertedId = db->getStorage().insert(Customer{0, userId, password, name, createdAt});
    Customer insertedCustomer = db->getStorage().get<Customer>(insertedId);
    return insertedCustomer;
}

bool CustomerDB::isExistUserId(std::string userId)
{
    BankDatabase *db = BankDatabase::getInstance();
    auto customer = db->getStorage().get_all<Customer>(where(c(&Customer::userId) == userId));
    if (customer.empty())
        return false; // 해당아이디의 고객 정보 없음.
    return true;
}

std::tuple<bool, const Customer> CustomerDB::GetCustomerByUserId(std::string userId)
{
    BankDatabase *db = BankDatabase::getInstance();
    auto customer = db->getStorage().get_all<Customer>(where(c(&Customer::userId) == userId));
    if (customer.empty())
        return {false, {0, "\0"}}; // 고객 조회 실패.
    return {true, customer[0]};
}

void CustomerDB::UpdateCustomerPassword(std::string userId, std::string password)
{
    BankDatabase *db = BankDatabase::getInstance();
    db->getStorage().update_all(set(c(&Customer::password) = password),
                                where(c(&Customer::userId) == userId));
}

void CustomerDB::UpdateCustomerName(std::string userId, std::string changingName)
{
    BankDatabase *db = BankDatabase::getInstance();
    db->getStorage().update_all(set(c(&Customer::name) = changingName),
                                where(c(&Customer::userId) == userId));
}

void CustomerDB::DeleteCustomer(std::string userId)
{
    // db에서 없애진 말자 transactionlog가 외래키로 잡혀있어서..
    // 고객에 딸린 account status false로
    // BankDatabase *db = BankDatabase::getInstance();
    // std::vector<Account> accounts = AccountDB::GetAccountsByCusId(cusId);
    // for (auto it = accounts.begin(); it != accounts.end(); ++it)
    // {
    //     it->status = false;
    // }
}
