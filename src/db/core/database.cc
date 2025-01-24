#include "database.h"

std::unique_ptr<Database> Database::instance = nullptr;

Database* Database::getInstance(const std::string& path) {
    return nullptr; // 실제 구현은 파생 클래스에서 수행
}
