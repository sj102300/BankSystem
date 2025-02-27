#include "services.h"

#include "grpcService/bankManagerImpl.h"

// 서버 실행 함수
void RunServer()
{
    const std::string server_address("0.0.0.0:3001");
    bankManagerImpl log_manager_service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort("0.0.0.0:3001", grpc::InsecureServerCredentials());
    builder.RegisterService(&log_manager_service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}