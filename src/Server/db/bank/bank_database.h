#pragma once

#include <sqlite_orm/sqlite_orm.h>

#include <iostream>

#include "core/database.h"
#include "myUtil.h"
#include "tables/accountdb.h"
#include "tables/customerdb.h"
#include "tables/fixedDepositdb.h"
#include "tables/savingsdb.h"
#include "tables/transaction_logdb.h"

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
    std::string db_full_path_;
    const std::string db_name_;

protected:
    BankDatabase(const std::string &path) : Database(path), db_name_("bank.db") {}

public:
    static BankDatabase *getInstance(const std::string &dbName = "bank.db")
    {
        if (!instance)
        {
            instance.reset(new BankDatabase(config::getRootDatabasePath() + dbName));
        }
        return static_cast<BankDatabase *>(instance.get());
    }

    void initStorage() override
    {
        db_full_path_ = std::string(config::getRootDatabasePath() + db_name_);
        if (!DatabaseUtils::ensureDatabaseFile(config::getRootDatabasePath(), db_name_))
        {
            std::cerr << "Failed to ensure database file: " << db_full_path_ << std::endl;
            return;
        }

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
