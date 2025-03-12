#pragma once

#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace config {
inline std::string getExecutablePath() { return std::filesystem::current_path().string(); }

inline std::string getCurrentDatabasePath(const std::string &dbName) {
    return (std::filesystem::path(getExecutablePath()) / dbName).string();
}
inline std::string getRootDatabasePath() { 
    std::filesystem::path homePath = std::getenv("HOME");
    return (homePath / "data/db/").string();
}
} // namespace config

class TimeStamp {
  public:
    static std::string get_current_time() {
        // 현재 시간을 가져옴
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);

        // 시간을 문자열로 변환
        std::ostringstream os;
        os << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");

        // 문자열을 값으로 반환
        return os.str();
    }
};

class DirectoryUtils {
  public:
    static bool exists(const std::string &path) { return std::filesystem::exists(path) && std::filesystem::is_directory(path); }

    static bool create(const std::string &path) {
        if (!exists(path)) {
            return std::filesystem::create_directories(path);
        }
        return true;
    }
};

class DatabaseUtils {
  public:
    static bool ensureDatabaseFile(const std::string &dirPath, const std::string &dbName) {
        if (!DirectoryUtils::exists(dirPath)) {
            if (!DirectoryUtils::create(dirPath)) {
                std::cerr << "Failed to create directory: " << dirPath << std::endl;
                return false;
            }
        }

        std::string dbFilePath = std::filesystem::path(dirPath) / dbName;

        if (!std::filesystem::exists(dbFilePath)) {
            std::ofstream dbFile(dbFilePath);
            if (!dbFile) {
                std::cerr << "Failed to create database file: " << dbFilePath << std::endl;
                return false;
            }
            dbFile.close();
            std::cout << "Database file created: " << dbFilePath << std::endl;
        }

        return true;
    }
};
