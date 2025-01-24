#pragma once

#include "core/database.h"
#include "models/customer.h"
#include "models/account.h"
#include "models/transaction_log.h"
#include <sqlite_orm/sqlite_orm.h>
#include "config.h"

using namespace sqlite_orm;

class BankDatabase : public Database {
private:
    using Storage = decltype(make_storage("",
        Customer::getTableDefinition(),
        Account::getTableDefinition(),
        TransactionLog::getTableDefinition()
    ));

    std::unique_ptr<Storage> storage;

protected:
    BankDatabase(const std::string& path) : Database(path) {}

public:
    static BankDatabase* getInstance(const std::string& dbName = "bank.db") {
        if (!instance) {
            instance.reset(new BankDatabase(config::getDatabasePath(dbName)));
        }
        return static_cast<BankDatabase*>(instance.get());
    }

    void initStorage() override {
        storage = std::make_unique<Storage>(make_storage(
            db_path,
            Customer::getTableDefinition(),
            Account::getTableDefinition(),
            TransactionLog::getTableDefinition()
        ));
        storage->sync_schema();
    }

    Storage& getStorage() { return *storage; }
};
