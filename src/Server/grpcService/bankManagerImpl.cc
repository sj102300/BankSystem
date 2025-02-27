#include "bankManagerImpl.h"

#include "customer_controller.h"
#include "account_controller.h"

#include <chrono>

bankManagerImpl::bankManagerImpl()
{
}

bankManagerImpl::~bankManagerImpl()
{
}

grpc::Status bankManagerImpl::signUp(grpc::ServerContext *context, const bank::customer::SignUpRequest *request, bank::customer::SignUpResponse *response)
{
    const auto [res, cus] = CustomerController::SignUp(request->userid(), request->password(), request->name());
    response->set_success(res);
    response->set_name(cus.name);
    response->set_userid(cus.userId);

    return grpc::Status();
}

grpc::Status bankManagerImpl::Login(grpc::ServerContext *context, const bank::customer::LogInRequest *request, bank::customer::LogInResponse *response)
{
    return grpc::Status();
}

grpc::Status bankManagerImpl::CreateFixedDepositAccount(grpc::ServerContext *context, const bank::account::CreateFixedDepositAccountRequest *request, bank::account::CreateFixedDepositAccountResponse *response)
{
    const auto res = AccountController::CreateFixedDepositAccount(request->cusid(), request->interestrate(), request->monthly_payment(), request->duedate());
    response->set_accnum(res.ainfo.accNum_);
    response->set_monthly_payment(res.finfo.monthlyPayment_);
    response->set_duedate(res.finfo.maturityDate_);

    return grpc::Status();
}

grpc::Status bankManagerImpl::deposit(grpc::ServerContext *context, const bank::DepositRequest *request, bank::DepositResponse *response)
{
    response->set_balance(10000);
    return grpc::Status::OK;
}
