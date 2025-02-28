#ifndef BANK_MANAGER_IMPL_H
#define BANK_MANAGER_IMPL_H

#include "bank.grpc.pb.h"
#include "account.grpc.pb.h"
#include "customer.grpc.pb.h"

#include <grpcpp/grpcpp.h>
#include <memory>
#include <string>

class bankManagerImpl : public bank::BankService::Service
{
private:
  std::shared_ptr<grpc::Channel> channel;
  std::unique_ptr<bank::BankService::Stub> stub;

public:
  bankManagerImpl();
  ~bankManagerImpl();

  grpc::Status signUp(grpc::ServerContext *context, const bank::customer::SignUpRequest *request, bank::customer::SignUpResponse *response);
  grpc::Status Login(grpc::ServerContext *context, const bank::customer::LogInRequest *request, bank::customer::LogInResponse *response);

  grpc::Status CreateFixedDepositAccount(grpc::ServerContext *context, const bank::account::CreateFixedDepositAccountRequest *request, bank::account::CreateFixedDepositAccountResponse *response);

  grpc::Status deposit(grpc::ServerContext *context, const bank::DepositRequest *request, bank::DepositResponse *response);
};

#endif // BANK_MANAGER_IMPL_H
