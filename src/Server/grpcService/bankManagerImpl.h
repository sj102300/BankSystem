#ifndef BANK_MANAGER_IMPL_H
#define BANK_MANAGER_IMPL_H

#include "bank.grpc.pb.h"
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

  grpc::Status deposit(grpc::ServerContext *context, const bank::DepositRequest *request, bank::DepositResponse *response);
};

#endif // BANK_MANAGER_IMPL_H
