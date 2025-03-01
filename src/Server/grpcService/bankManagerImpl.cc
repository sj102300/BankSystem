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

grpc::Status bankManagerImpl::SignUp(grpc::ServerContext *context, const bank::customer::SignUpRequest *request, bank::customer::SignUpResponse *response)
{
    const auto [res, cus] = CustomerController::SignUp(request->userid(), request->password(), request->name());
    
    response->set_success(res);
    if(res){
        response->set_msg("sucess");
        response->set_name(cus.name);
        response->set_userid(cus.userId);
    }
    else{
        response->set_msg("중복된 아이디");
    }

    return grpc::Status();
}

grpc::Status bankManagerImpl::Login(grpc::ServerContext *context, const bank::customer::LogInRequest *request, bank::customer::LogInResponse *response)
{
    const auto [res, cus] = CustomerController::Login(request->userid(), request->password());

    response->set_success(res);
    if(res){
        response->set_msg("sucess");
        // response->set_
    }

    return grpc::Status();
}

grpc::Status bankManagerImpl::CreateFixedDepositAccount(grpc::ServerContext *context, const bank::account::CreateFixedDepositAccountRequest *request, bank::account::CreateFixedDepositAccountResponse *response)
{
    // const auto res = AccountController::CreateFixedDepositAccount(request->cusid(), request->interestrate(), request->monthly_payment(), request->duedate());
    response->set_accnum(res.ainfo.accNum_);
    response->set_monthly_payment(res.finfo.monthlyPayment_);
    response->set_duedate(res.finfo.maturityDate_);

    return grpc::Status();
}

grpc::Status

// grpc::Status bankManagerImpl::deposit(grpc::ServerContext *context, const bank::DepositRequest *request, bank::DepositResponse *response)
// {
//     response->set_balance(10000);
//     return grpc::Status::OK;
// }
