#pragma once
#include <sqlite_orm/sqlite_orm.h>
#include <string>
#include <tuple>

class BankDatabase;
using namespace sqlite_orm;

struct Customer
{
    unsigned int cusId;
    std::string userId;
    std::string password;
    std::string name;
    std::string createdAt;

    static auto getTableDefinition()
    {
        return make_table(
            "Customer",
            make_column("cusId", &Customer::cusId, primary_key().autoincrement()),
            make_column("userId", &Customer::userId, unique()),
            make_column("password", &Customer::password),
            make_column("name", &Customer::name),
            make_column("createdAt", &Customer::createdAt));
    }
};

class CustomerDB
{
public:
    CustomerDB();
    static Customer CreateCustomer(std::string &name);
    static bool isExistByCusId(int cusId);
    static std::tuple<bool, const Customer> GetCustomer(int cusId);
    static std::tuple<bool, const Customer> GetCustomer(std::string &name);
    static void UpdateCustomer(int cusId, std::string &changing_name);
    static void DeleteCustomer(int cusId);
};

// BankDatabase* CustomerDB::db = BankDatabase::getInstance();