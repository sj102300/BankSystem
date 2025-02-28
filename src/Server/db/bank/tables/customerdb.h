#pragma once
#include <sqlite_orm/sqlite_orm.h>
#include <string>
#include <tuple>

class BankDatabase;
using namespace sqlite_orm;

struct Customer
{
    unsigned int cusId;
    std::string userId;  //계정 회원아이디
    std::string password;
    std::string name;
    std::string created_at;

    static auto getTableDefinition()
    {
        return make_table(
            "Customer",
            make_column("cusId", &Customer::cusId, primary_key().autoincrement()),
            make_column("userId", &Customer::userId, unique()),
            make_column("password", &Customer::password),
            make_column("name", &Customer::name),
            make_column("createdAt", &Customer::created_at));
    }
};

class CustomerDB
{
public:
    CustomerDB();
    static Customer CreateCustomer(std::string userId, std::string password, std::string name);
    static bool isExistUserId(std::string userId);
    static std::tuple<bool, const Customer> GetCustomerByUserId(std::string userId);
    static void UpdateCustomerPassword(std::string userId, std::string password);
    static void UpdateCustomerName(std::string userId, std::string changingName);
    static void DeleteCustomer(std::string userId);  //회원탈퇴 - 구현예정.. 아직 구현안해해
};