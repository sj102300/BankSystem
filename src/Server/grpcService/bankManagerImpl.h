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

  grpc::Status SignUp(::grpc::ServerContext* context, const ::bank::customer::SignUpRequest* request, ::bank::customer::SignUpResponse* response) override;
  grpc::Status Login(grpc::ServerContext *context, const bank::customer::LogInRequest *request, bank::customer::LogInResponse *response);

  grpc::Status CreateFixedDepositAccount(grpc::ServerContext *context, const bank::account::CreateFixedDepositAccountRequest *request, bank::account::CreateFixedDepositAccountResponse *response);
  grpc::Status CreateNormalSavingsAccount(grpc::ServerContext *context, const bank::account::CreateNormalSavingsAccountRequest *request, bank::account::CreateNormalSavingsAccountResponse *response);
  
  grpc::Status ListTransactionLogsByAccNum(grpc::ServerContext *context, const bank::account::ListTransactionLogsRequest *request, bank::account::ListTransactionLogsResponse *response);
  grpc::Status ListAccountsByUserId(grpc::ServerContext *context, const bank::account::ListAccountsByUserIdRequest *request, bank::account::ListAccountsByUserIdResponse *response);

  grpc::Status Transfer(grpc::ServerContext *context, const bank::account::TransferRequest *request, bank::account::TransferResponse *response);
};

#endif // BANK_MANAGER_IMPL_H
