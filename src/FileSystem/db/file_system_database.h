#include "database.h"
#include "account_file_info.h"
#include <sqlite_orm/sqlite_orm.h>
using namespace sqlite_orm;

#include <filesystem>

namespace
{
    inline std::string getExecutablePath()
    {
        return std::filesystem::current_path().string();
    }

    inline std::string getDatabasePath(const std::string &dbName)
    {
        return (std::filesystem::path(getExecutablePath()) / dbName).string();
    }
}

class FileSystemDatabase : public Database
{
private:
    using Storage = decltype(make_storage("FileSystem", AccountFileInfo::getTableDefinition()));

    std::unique_ptr<Storage> storage;
    FileSystemDatabase(const std::string &path) : Database(path) {}

public:
    static FileSystemDatabase *getInstance(const std::string &dbName = "file_system.db")
    {
        if (!instance)
        {
            instance.reset(new FileSystemDatabase(getDatabasePath(dbName))); // 이거 왜 config로 경로 설정하는지
        }
        return static_cast<FileSystemDatabase *>(instance.get());
    }
    void initStorage() override
    {
        storage = std::make_unique<Storage>(make_storage(
            db_path, AccountFileInfo::getTableDefinition()));
        storage->sync_schema();
    }

    Storage& getStorage(){
        return *storage;
    }
};