#include "bankManagerImpl.h"
#include <chrono>

bankManagerImpl::bankManagerImpl()
{
}

bankManagerImpl::~bankManagerImpl()
{
}

grpc::Status bankManagerImpl::deposit(grpc::ServerContext *context, const bank::DepositRequest *request, bank::DepositResponse *response)
{
    response->set_balance(10000);
    return grpc::Status::OK;
}
