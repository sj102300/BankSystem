
#include "file_system_database.h"
#include <vector>
/**
unsigned int fileId; //auto increment
unsigned int account_type;
unsigned int file_type;
std::string path; */

void AccountFileInfoDB::CreateFile(unsigned int file_category, unsigned int account_type, std::string path)
{
    FileSystemDatabase *db = FileSystemDatabase::getInstance();
    db->getStorage().insert(AccountFileInfo{
        0,
        file_category,
        account_type,
        path,
        "", // 나중에 해싱해서 업데이트
        true});
}

std::tuple<bool, std::string> AccountFileInfoDB::GetFilePath(unsigned int file_category, unsigned int account_type)
{
    FileSystemDatabase *db = FileSystemDatabase::getInstance();
    std::vector<AccountFileInfo> ret = db->getStorage().get_all<AccountFileInfo>(where(file_category == c(&AccountFileInfo::file_category) && account_type == c(&AccountFileInfo::account_type)));
    if(ret.empty()){
        return {false, ""};
    }
    return {true, ret.at(0).path};
}

void AccountFileInfoDB::UpdateFilePath()
{
    
}

void AccountFileInfoDB::DeleteFile()
{
}