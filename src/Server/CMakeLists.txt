cmake_minimum_required(VERSION 3.10)

# Project name
project(server)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debug mode 설정
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
endif()

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/BankSystem
    ${CMAKE_CURRENT_SOURCE_DIR}/db
    ${CMAKE_CURRENT_SOURCE_DIR}/db/core
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank/models
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank/utils
)

# Configure file for paths
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
    "${CMAKE_BINARY_DIR}/config.h"
)
include_directories(${CMAKE_BINARY_DIR})

# SQLite ORM
include(FetchContent)
FetchContent_Declare(
    sqlite_orm
    GIT_REPOSITORY https://github.com/fnc12/sqlite_orm.git
    GIT_TAG v1.9
)
FetchContent_MakeAvailable(sqlite_orm)

# Source files for database
set(DB_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/db/core/database.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank/models/accountdb.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank/models/customerdb.cc
)

# Header files for database
set(DB_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/db/core/database.h
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank/bank_database.h
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank/models/accountdb.h
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank/models/customerdb.h
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank/models/transaction_logdb.h
)

# Main application source files (excluding unnecessary files)
set(APP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BankSystem/atm.cc
)

# Main application header files
set(APP_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/BankSystem/atm.h
    ${CMAKE_CURRENT_SOURCE_DIR}/BankSystem/common_option.h
)

# SQLite3 library
find_package(SQLite3 REQUIRED)
if (NOT SQLite3_FOUND)
    message(FATAL_ERROR "SQLite3 library not found!")
endif()

# Add executable
add_executable(${PROJECT_NAME} 
    ${APP_SOURCES} 
    ${APP_HEADERS}
    ${DB_SOURCES}
    ${DB_HEADERS}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    SQLite::SQLite3 
    sqlite_orm
)
