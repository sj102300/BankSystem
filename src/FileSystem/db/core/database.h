#ifndef __FILESYSTEM_DATABASE_H__
#define __FILESYSTEN_DATABASE_H__

#include <sqlite_orm/sqlite_orm.h>
#include <string>
#include <memory>

class Database {
protected:
    static std::unique_ptr<Database> instance;
    std::string db_path;

    Database(const std::string& path);

public:
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    static Database* getInstance(const std::string& path = "file_system.db");
    virtual void initStorage() = 0;
};

#endif