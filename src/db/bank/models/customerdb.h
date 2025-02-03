#pragma once
#include <sqlite_orm/sqlite_orm.h>

#include <string>

#include "bank_database.h"

class BankDatabase;

struct Customer
{
    int cusId;
    std::string cus_name;

    static auto getTableDefinition()
    {
        return sqlite_orm::make_table(
            "Customer",
            sqlite_orm::make_column("cusId", &Customer::cusId,
                                    sqlite_orm::primary_key()),
            sqlite_orm::make_column("cus_name", &Customer::cus_name));
    }
};

class CustomerDB
{
public:
    CustomerDB();
    static int CreateCustomer(std::string &name);
    static bool isExistByCusId(int cusId);
    static const int GetCustomerId(int name);
    static std::string &GetCustomerName(int cusId);
    static void UpdateCustomer(int cusId, std::string &changing_name);
    static void DeleteCustomer(int cusId);
};

// BankDatabase* CustomerDB::db = BankDatabase::getInstance();