cmake_minimum_required(VERSION 3.10)
# Project name
project(BankServer)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debug mode 설정
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
endif()

####### proto 영역 #######

# 필요한 .proto 파일 이름 설정 (확장자 제외, 여러 개 가능)
set(PROTO_NAMES bank)

# 생성된 파일들의 경로 설정
set(PROTO_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../protos_build)
set(PROTO_SOURCES "")
set(PROTO_HEADERS "")

foreach(PROTO_NAME ${PROTO_NAMES})
    list(APPEND PROTO_SOURCES
        ${PROTO_BUILD_DIR}/${PROTO_NAME}.pb.cc
        ${PROTO_BUILD_DIR}/${PROTO_NAME}.grpc.pb.cc
    )
    list(APPEND PROTO_HEADERS
        ${PROTO_BUILD_DIR}/${PROTO_NAME}.pb.h
        ${PROTO_BUILD_DIR}/${PROTO_NAME}.grpc.pb.h
    )
endforeach()

# 출력 확인 (디버그용)
message(STATUS "Generated PROTO_SOURCES: ${PROTO_SOURCES}")
message(STATUS "Generated PROTO_HEADERS: ${PROTO_HEADERS}")

# 결과를 상위 CMake에서 사용할 수 있도록 설정 (필요시)
set(PROTO_SOURCES ${PROTO_SOURCES} PARENT_SCOPE)
set(PROTO_HEADERS ${PROTO_HEADERS} PARENT_SCOPE)

###########################################################

# 해당 라인부터 수정
####### 외부 라이브러리 영역 #######
# SQLite ORM
include(FetchContent)
FetchContent_Declare(
    sqlite_orm
    GIT_REPOSITORY https://github.com/fnc12/sqlite_orm.git
    GIT_TAG v1.9
)
FetchContent_MakeAvailable(sqlite_orm)

# SQLite3 library
find_package(SQLite3 REQUIRED)
if (NOT SQLite3_FOUND)
message(FATAL_ERROR "SQLite3 library not found!")
endif()
#################################

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/db
    ${CMAKE_CURRENT_SOURCE_DIR}/db/core
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank/models
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank/controller
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank/tables
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank/models/Accout
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank/models/Customer
    ${CMAKE_CURRENT_SOURCE_DIR}/db/bank/models/Log
    ${CMAKE_CURRENT_SOURCE_DIR}/grpcService
    ${CMAKE_CURRENT_SOURCE_DIR}/../../protos_build
)

# Configure file for paths
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
    "${CMAKE_BINARY_DIR}/config.h"
)
include_directories(${CMAKE_BINARY_DIR})

# Define the list of directories to search
set(SOURCE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Initialize empty lists
set(SOURCES "")
set(HEADERS "")

# Loop through each directory and collect source/header files
foreach(DIR ${SOURCE_DIRS})
    file(GLOB_RECURSE TMP_SOURCES ${DIR}/*.cc)
    file(GLOB_RECURSE TMP_HEADERS ${DIR}/*.h)
    
    list(APPEND SOURCES ${TMP_SOURCES})
    list(APPEND HEADERS ${TMP_HEADERS})
endforeach()

# Print collected files for debugging
message(STATUS "Collected Sources: ${SOURCES}")
message(STATUS "Collected Headers: ${HEADERS}")

# Add executable
add_executable(${PROJECT_NAME} 
    ${SOURCES} 
    ${HEADERS}
)

# 프로토콜 버퍼 소스 파일 추가
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

add_library(grpc_lib
  ${PROTO_SOURCES}
  ${PROTO_HEADERS})
target_link_libraries(grpc_lib
  absl::check
  gRPC::grpc++_reflection
  gRPC::grpc++
  protobuf::libprotobuf)

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    SQLite::SQLite3 
    sqlite_orm
    grpc_lib
)
