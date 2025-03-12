#include <unordered_map>
#include <string>

class AccountFileInfoController{
private:
    std::unordered_map<unsigned int, std::string> filemap;

public:
    std::string getFilePath(unsigned int account_type, unsigned int file_category);
    // bool addFile();
};