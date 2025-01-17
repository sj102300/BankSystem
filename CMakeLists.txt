cmake_minimum_required(VERSION 3.10)
project(BankSystem)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 헤더 파일 디렉토리 추가
include_directories(${CMAKE_SOURCE_DIR}/BankSystem)

# 소스 파일들
set(SOURCES
    BankSystem/account.cc
    BankSystem/atm.cc
    BankSystem/customer.cc
    main.cpp
)

# 실행 파일 생성
add_executable(BankSystem ${SOURCES})