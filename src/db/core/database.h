#pragma once

#include <sqlite_orm/sqlite_orm.h>
#include <string>
#include <memory>

class Database {
protected:
    static std::unique_ptr<Database> instance;
    std::string db_path;

    Database(const std::string& path) : db_path(path) {}

public:
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    static Database* getInstance(const std::string& path = "bank.db");
    virtual void initStorage() = 0;
};
