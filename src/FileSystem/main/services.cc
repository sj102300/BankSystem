#include "services.h"

#include "grpcService/fileSystemManagerImpl.h"

#define FILESYSTEM_IP "0.0.0.0:3002"
// 서버 실행 함수
void RunServer()
{
    const std::string server_address(FILESYSTEM_IP);
    FileSystemManagerImpl log_manager_service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(FILESYSTEM_IP, grpc::InsecureServerCredentials());
    builder.RegisterService(&log_manager_service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}