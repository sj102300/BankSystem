#!/bin/bash

# 현재 스크립트가 위치한 디렉토리로 이동
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

# 이제 이 위치를 기준으로 실행 가능
echo "Running from: $SCRIPT_DIR"

# protoc 및 grpc_cpp_plugin 경로 확인
PROTOC=$(which protoc)
GRPC_PLUGIN=$(which grpc_cpp_plugin)

# 필수 파일 확인
if [ -z "$PROTOC" ]; then
    echo "Error: protoc not found!"
    exit 1
fi

if [ -z "$GRPC_PLUGIN" ]; then
    echo "Error: grpc_cpp_plugin not found!"
    exit 1
fi

# # .proto 파일이 위치한 디렉토리
# PROTO_SRC_DIR="./protos"
# # 생성된 파일을 저장할 디렉토리
# GENERATED_SRC_DIR="./protos_build"
# # Include 경로 설정
# PROTO_INCLUDE_DIRS=(
#     "./protos"
#     "/usr/local/include"
# )

# # 출력 디렉토리가 없으면 생성
# if [ ! -d "$GENERATED_SRC_DIR" ]; then
#     echo "Creating output directory: $GENERATED_SRC_DIR"
#     mkdir -p "$GENERATED_SRC_DIR"
# fi

# # Include 경로를 위한 -I 옵션 구성
# PROTO_INCLUDE_FLAGS=""
# for dir in "${PROTO_INCLUDE_DIRS[@]}"; do
#     PROTO_INCLUDE_FLAGS="$PROTO_INCLUDE_FLAGS -I$dir"
# done

# # .proto 파일 처리
# PROTO_FILES=$(find "$PROTO_SRC_DIR" -name "*.proto")
# for PROTO_FILE in $PROTO_FILES; do
#     PROTO_NAME=$(basename "$PROTO_FILE" .proto)
#     PB_CC_FILE="${GENERATED_SRC_DIR}/${PROTO_NAME}.pb.cc"
#     GRPC_PB_CC_FILE="${GENERATED_SRC_DIR}/${PROTO_NAME}.grpc.pb.cc"

#     echo "Processing $PROTO_FILE..."

#     # protoc 명령 실행
#     $PROTOC $PROTO_INCLUDE_FLAGS \
#         --cpp_out="$GENERATED_SRC_DIR" \
#         --grpc_out="$GENERATED_SRC_DIR" \
#         --plugin=protoc-gen-grpc="$GRPC_PLUGIN" \
#         "$PROTO_FILE"

#     # 결과 파일 확인
#     if [ ! -f "$PB_CC_FILE" ] || [ ! -f "$GRPC_PB_CC_FILE" ]; then
#         echo "Error: Failed to generate files for $PROTO_FILE"
#         exit 1
#     fi

#     echo "Generated: $PB_CC_FILE, $GRPC_PB_CC_FILE"
# done

# echo "All .proto files processed successfully!"

# 소스 및 빌드 디렉토리 설정
declare -A PROTO_SRC_DIRS
PROTO_SRC_DIRS["FileSystem"]="./protos/FileSystem"
PROTO_SRC_DIRS["Server"]="./protos/Server"

PROTO_BUILD_DIR="./protos_build"

# 공통 Include 경로 (둘 다 필요)
COMMON_INCLUDE="/usr/local/include"

# 빌드 디렉토리 초기화 (기존 내용 삭제 후 재생성)
if [ -d "$PROTO_BUILD_DIR" ]; then
    echo "Cleaning existing build directory: $PROTO_BUILD_DIR"
    rm -rf "$PROTO_BUILD_DIR"
fi
mkdir -p "$PROTO_BUILD_DIR"


# 각 프로토콜 소스 디렉토리를 순회하며 컴파일
for KEY in "${!PROTO_SRC_DIRS[@]}"; do
    PROTO_SRC_DIR="${PROTO_SRC_DIRS[$KEY]}"
    DEST_DIR="$PROTO_BUILD_DIR/$KEY"

    # 해당 빌드 디렉토리 생성
    mkdir -p "$DEST_DIR"

    # Include 옵션 설정 (해당 디렉토리 + 공통 Include)
    INCLUDE_FLAGS="-I=protos/$KEY -I=$COMMON_INCLUDE"

    # .proto 파일 목록 찾기
    PROTO_FILES=$(find "$PROTO_SRC_DIR" -name "*.proto")

    # 개별 파일 컴파일
    for proto_file in $PROTO_FILES; do
        echo "Compiling $proto_file -> $DEST_DIR"
        $PROTOC $INCLUDE_FLAGS \
                --cpp_out="$DEST_DIR" \
                --grpc_out="$DEST_DIR" \
                --plugin=protoc-gen-grpc="$GRPC_PLUGIN" \
                "$proto_file"
    done
done

echo "Proto files compilation completed!"