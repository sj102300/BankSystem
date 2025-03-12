#include <gtest/gtest.h>
#include <grpcpp/grpcpp.h>
#include "bank.grpc.pb.h"

using ::grpc::ClientContext;
using ::grpc::Status;
using ::bank::customer::SignUpRequest;
using ::bank::customer::SignUpResponse;
using ::bank::customer::LogInRequest;
using ::bank::customer::LogInResponse;
using ::bank::BankService;

const std::string addr("127.0.0.1:3001");

class BankServiceStub {
public:
    // 싱글톤 인스턴스 반환
    static BankServiceStub* GetInstance(const std::string& server_address = "localhost:50051") {
        static std::unique_ptr<BankServiceStub> instance_;
        if (!instance_) {
            instance_ = std::unique_ptr<BankServiceStub>(new BankServiceStub(server_address));
        }
        return instance_.get();
    }

    // gRPC 요청: 회원가입 (SignUp)
    Status SignUp(ClientContext* context, const SignUpRequest& request, SignUpResponse* response) {
        return stub_->SignUp(context, request, response);
    }

    // gRPC 요청: 로그인 (Login)
    Status Login(ClientContext* context, const LogInRequest& request, LogInResponse* response) {
        return stub_->Login(context, request, response);
    }

private:
    // gRPC Stub
    std::unique_ptr<BankService::Stub> stub_;

    // private 생성자 (싱글톤)
    explicit BankServiceStub(const std::string& server_address) {
        auto channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
        stub_ = BankService::NewStub(channel);
    }
};

TEST(ServerTest, SignUp) {
    auto* client = BankServiceStub::GetInstance(addr);

    SignUpRequest request;
    request.set_name("gtest");
    request.set_userid("admin");
    request.set_password("qwe123");

    SignUpResponse response;
    ClientContext context;

    Status status = client->SignUp(&context, request, &response);
    EXPECT_TRUE(response.status());
}

TEST(ServerTest, Login) {
    auto* client = BankServiceStub::GetInstance(addr);

    LogInRequest request;
    request.set_userid("admin");
    request.set_password("qwe123");

    LogInResponse response;
    ClientContext context;

    Status status = client->Login(&context, request, &response);
    EXPECT_TRUE(response.status());
}

TEST(ServerTest, FailLogin) {
    auto* client = BankServiceStub::GetInstance(addr);

    LogInRequest request;
    request.set_userid("admin");
    request.set_password("qwe123!@#");

    LogInResponse response;
    ClientContext context;

    Status status = client->Login(&context, request, &response);
    EXPECT_TRUE(!response.status());
}
