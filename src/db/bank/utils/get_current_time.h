#ifndef __GET_CURRENT_TIME_H__
#define __GET_CURRENT_TIME_H__

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

class TimeStamp{
public:
    static const std::string& get_current_time() {
        std::chrono::system_clock::time_point createdAt(std::chrono::system_clock::now());
        std::time_t time = std::chrono::system_clock::to_time_t(createdAt);
        std::ostringstream os;
        os << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        return os.str();
    }
};

#endif