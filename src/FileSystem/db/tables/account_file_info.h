
#include <sqlite_orm/sqlite_orm.h>
#include <string>

using namespace sqlite_orm;

struct AccountFileInfo{
    unsigned int account_fileId; //auto increment
    unsigned int file_category;
    unsigned int account_type;
    std::string path;
    std::string hashNumber;
    bool status;

    static auto getTableDefinition()
    {
        return make_table(
            "AccountFileInfo",
            make_column("AccountFileId", &AccountFileInfo::account_fileId, primary_key().autoincrement()),
            make_column("fileCategory", &AccountFileInfo::file_category),
            make_column("accountType", &AccountFileInfo::account_type),
            make_column("path", &AccountFileInfo::path),
            make_column("hashNumber", &AccountFileInfo::hashNumber),
            make_column("status", &AccountFileInfo::status)
        );
    }
};

class AccountFileInfoDB{
public:
    static void CreateFile(unsigned int file_category, unsigned int account_type, std::string path);
    static std::tuple<bool, std::string> GetFilePath(unsigned int file_category, unsigned int account_type);
    static void UpdateFilePath();  //아직 필요없어
    static void DeleteFile();
};