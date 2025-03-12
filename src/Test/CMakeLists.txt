cmake_minimum_required(VERSION 3.10)

project(Test)

# enable_testing()을 통해 유닛 테스트 수행을 선언한다.
enable_testing()

# 각 테스트 디렉토리 추가
add_subdirectory(Server)