
cmake_minimum_required(VERSION 3.10)

project(ServerTest)

find_package(GTest REQUIRED)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../protos_build/Server
)

set(SOURCE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../protos_build/Server
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


# 테스트 소스 파일 목록
set(TEST_SOURCES
    test_main.cpp
    test_example.cpp
    test_rpc.cpp
)

# 중복된 grpc_lib 생성 방지: 기존 라이브러리를 사용
add_executable(ServerTest ${TEST_SOURCES} ${SOURCES} ${HEADERS})

# Server에서 정의된 grpc_lib를 포함하여 링크
target_link_libraries(ServerTest PRIVATE
    GTest::GTest
    GTest::Main
    protobuf::libprotobuf
    gRPC::grpc++
    gRPC::grpc++_reflection
    grpc_lib  # 기존 Server에서 정의된 라이브러리 사용
)

# 테스트 등록
add_test(NAME ServerTests COMMAND ServerTest)
