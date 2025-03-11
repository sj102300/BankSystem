#include <unordered_map>
#include <string>

class FilePathController{
private:
    std::unordered_map<unsigned int, std::string> filemap;

public:
    std::string getFilePath();
    bool addFile();
};

//DB를 붙일지말지