#include <sqlite_orm/sqlite_orm.h>

#include "database.h"
#include "account_file_info.h"
#include "myUtil.h"

using namespace sqlite_orm;

#include <filesystem>


class FileSystemDatabase : public Database
{
private:
    using Storage = decltype(make_storage("FileSystem", AccountFileInfo::getTableDefinition()));

    std::unique_ptr<Storage> storage;
    std::string db_full_path_;
    const std::string db_name_;

protected:
    FileSystemDatabase(const std::string &path) : Database(path), db_name_("file_system.db") {}

public:
    static FileSystemDatabase *getInstance(const std::string &dbName = "file_system.db")
    {
        if (!instance)
        {
            instance.reset(new FileSystemDatabase(config::getRootDatabasePath() + dbName)); // 이거 왜 config로 경로 설정하는지
        }
        return static_cast<FileSystemDatabase *>(instance.get());
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
            db_path, AccountFileInfo::getTableDefinition()));
        storage->sync_schema();
    }

    Storage& getStorage(){
        return *storage;
    }
};