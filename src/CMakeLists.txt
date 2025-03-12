cmake_minimum_required(VERSION 3.16)
project(BankSystem)

# 프로젝트 이름 및 언어 설정
project(ProtoBuild CXX)

# Protobuf 및 gRPC 패키지 찾기
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC REQUIRED)

# .proto 파일 및 include 디렉토리 설정
set(PROTO_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protos)
set(PROTO_INCLUDE_DIRS 
    ${PROTO_SRC_DIR}
    /usr/local/include
)

# .proto 파일 탐색
file(GLOB_RECURSE PROTO_FILES "${PROTO_SRC_DIR}/*.proto")

# 생성된 파일들을 저장할 디렉토리 설정
set(GENERATED_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../protos_build)

# 출력 디렉토리가 존재하지 않을 경우 생성
file(MAKE_DIRECTORY ${GENERATED_SRC_DIR})

# protoc 스크립트 실행
execute_process(
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../generate_protos.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE SCRIPT_RESULT
)

# 스크립트 실행 결과 확인
if (SCRIPT_RESULT)
    message(FATAL_ERROR "Failed to run generate_protos.sh")
endif()

# Include 디렉토리를 위한 -I 옵션 설정
set(PROTO_INCLUDE_FLAGS "")
foreach(dir ${PROTO_INCLUDE_DIRS})
    list(APPEND PROTO_INCLUDE_FLAGS "-I${dir}")
endforeach()

message(status "include path : ${PROTO_INCLUDE_FLAGS}")

# protoc 경로를 명시적으로 찾기
find_program(PROTOC_EXECUTABLE protoc REQUIRED)

# grpc_cpp_plugin 경로 찾기
find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin REQUIRED)

include_directories(${GENERATED_SRC_DIR})

# Client와 Server를 하위 디렉터리로 추가
# add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(FileSystem)