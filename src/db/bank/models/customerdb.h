#pragma once
#include <sqlite_orm/sqlite_orm.h>
#include <string>

#include "bank_database.h"

class BankDatabase;

struct Customer {
    int cusId;
    std::string cus_name;

    static auto getTableDefinition() {
        return sqlite_orm::make_table("Customer", sqlite_orm::make_column("cusId", &Customer::cusId, sqlite_orm::primary_key()),
                                      sqlite_orm::make_column("cus_name", &Customer::cus_name));
    }
};

class CustomerDB {
  private:
    BankDatabase *db;

  public:
    CustomerDB();
    int CreateCustomer(std::string &name);
    bool isExistByCusId(int cusId);
    const int GetCustomerId(int name);
    std::string &GetCustomerName(int cusId);
    void UpdateCustomer(int cusId, std::string &changing_name);
    void DeleteCustomer(int cusId);
};

// BankDatabase* CustomerDB::db = BankDatabase::getInstance();