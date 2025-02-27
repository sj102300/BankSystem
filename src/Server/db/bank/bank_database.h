#pragma once

#include <sqlite_orm/sqlite_orm.h>

#include <iostream>

#include "config.h"
#include "core/database.h"
#include "models/accountdb.h"
#include "models/customerdb.h"
#include "models/transaction_logdb.h"
#include "models/fixedDeposit.h"
#include "models/savings.h"

using namespace sqlite_orm;

class BankDatabase : public Database
{
private:
    using Storage = decltype(make_storage("", Customer::getTableDefinition(),
                                          Account::getTableDefinition(),
                                          TransactionLog::getTableDefinition(),
                                          Savings::getTableDefinition(),
                                          FixedDeposit::getTableDefinition()));

    std::unique_ptr<Storage> storage;

protected:
    BankDatabase(const std::string &path) : Database(path) {}

public:
    static BankDatabase *getInstance(const std::string &dbName = "bank.db")
    {
        if (!instance)
        {
            instance.reset(new BankDatabase(config::getDatabasePath(dbName)));
        }
        return static_cast<BankDatabase *>(instance.get());
    }

    void initStorage() override
    {
        storage = std::make_unique<Storage>(make_storage(
            db_path, Customer::getTableDefinition(), Account::getTableDefinition(),
            TransactionLog::getTableDefinition(),
            Savings::getTableDefinition(),
            FixedDeposit::getTableDefinition()));
        storage->sync_schema();
    }

    void handleException(std::exception &e)
    {
        std::cerr << "DB 오류 발생" << e.what() << std::endl;
    }

    Storage &getStorage() { return *storage; }
};
