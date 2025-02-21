#ifndef __GET_CURRENT_TIME_H__
#define __GET_CURRENT_TIME_H__

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

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
#endif