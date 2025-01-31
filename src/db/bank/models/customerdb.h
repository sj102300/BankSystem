#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>

struct Customer {
    int cusId;
    std::string cus_name;

    static auto getTableDefinition() {
        return sqlite_orm::make_table("Customer",
            sqlite_orm::make_column("cusId", &Customer::cusId, sqlite_orm::primary_key()),
            sqlite_orm::make_column("cus_name", &Customer::cus_name));
    }
};

class CustomerDB: public BankDatabase{
private:
    static BankDatabase* db;

public:
    void CreateCustomer(std::string& name);
    bool isExistByCusId(int cusId);
    std::string& GetCustomerName(int cusId);
    void UpdateCustomer(int cusId, std::string& changing_name);
    void DeleteCustomer(int cusId);
};

BankDatabase* CustomerDB::db = BankDatabase::getInstance();