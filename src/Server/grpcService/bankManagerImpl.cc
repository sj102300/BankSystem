#include "bankManagerImpl.h"

#include "customer_controller.h"
#include "account_controller.h"
#include "transaction_controller.h"

bankManagerImpl::bankManagerImpl() {}
bankManagerImpl::~bankManagerImpl() {}

grpc::Status bankManagerImpl::SignUp(grpc::ServerContext *context, const bank::customer::SignUpRequest *request, bank::customer::SignUpResponse *response)
{
    const auto [res, msg] = CustomerController::SignUp(request->userid(), request->password(), request->name());

    response->set_status(res);
    response->set_message(msg);
    if (res)
    {
        Customer cus = CustomerController::GetCustomerInfo(request->userid());
        response->set_userid(cus.userId);
        response->set_name(cus.name);
    }

    return grpc::Status();
}

grpc::Status bankManagerImpl::Login(grpc::ServerContext *context, const bank::customer::LogInRequest *request, bank::customer::LogInResponse *response)
{
    const auto [res, msg] = CustomerController::Login(request->userid(), request->password());

    response->set_status(res);
    response->set_message(msg);

    if (res)
    {
        Customer cus = CustomerController::GetCustomerInfo(request->userid());
        response->set_userid(cus.userId);
        response->set_name(cus.name);
    }

    return grpc::Status();
}

grpc::Status bankManagerImpl::CreateFixedDepositAccount(grpc::ServerContext *context, const bank::account::CreateFixedDepositAccountRequest *request, bank::account::CreateFixedDepositAccountResponse *response)
{
    const auto [res, msg] = AccountController::CreateFixedDepositAccount(request->userid(), request->interest_rate(), request->monthly_payment(), request->duedate());

    response->set_status(res);
    response->set_message(res ? "계좌 생성 성공" : "계좌 생성 실패");

    if (res)
    {
        Account acc = AccountController::GetAccountByAccNum(msg);
        response->set_accnum(acc.accNum);
    }

    return grpc::Status();
}

grpc::Status bankManagerImpl::CreateNormalSavingsAccount(grpc::ServerContext *context, const bank::account::CreateNormalSavingsAccountRequest *request, bank::account::CreateNormalSavingsAccountResponse *response)
{
    const auto [res, msg] = AccountController::CreateNormalSavingsAccount(request->userid(), request->interest_rate());

    response->set_status(res);
    response->set_message(res ? "계좌 생성 성공" : "계좌 생성 실패");

    if (res)
    {
        Account acc = AccountController::GetAccountByAccNum(msg);
        response->set_accnum(acc.accNum);
    }

    return grpc::Status();
}

grpc::Status bankManagerImpl::ListTransactionLogsByAccNum(grpc::ServerContext *context, const bank::account::ListTransactionLogsRequest *request, bank::account::ListTransactionLogsResponse *response)
{

    std::vector<TransactionLog> logs = AccountController::GetAccountLogs(request->accnum());

    response->set_status(true);
    for (const auto &log : logs)
    {
        auto *new_log = response->add_logs();
        new_log->set_logid(log.logId);
        new_log->set_accnum(log.accNum);
        new_log->set_userid(log.userId);
        new_log->set_trade_amount(log.trade_amount);
        new_log->set_created_at(log.created_at);
        new_log->set_remaining_balance(log.remaining_balance);
        new_log->set_transaction_type(log.transaction_type);
    }

    return grpc::Status();
}

grpc::Status bankManagerImpl::ListAccountsByUserId(grpc::ServerContext *context, const bank::account::ListAccountsByUserIdRequest *request, bank::account::ListAccountsByUserIdResponse *response)
{

    std::vector<Account> accounts = AccountController::GetAccountsByUserId(request->userid());

    response->set_status(true);
    for (const auto &account : accounts)
    {
        auto *new_account = response->add_accounts();
        new_account->set_accnum(account.accNum);
        new_account->set_userid(account.userId);
        new_account->set_account_type(account.account_type);
        new_account->set_status(account.status);
        new_account->set_created_at(account.created_at);
    }

    return grpc::Status();
}

grpc::Status bankManagerImpl::Transfer(grpc::ServerContext *context, const bank::account::TransferRequest *request, bank::account::TransferResponse *response)
{

    const auto [res, msg] = TransactionController::Transfer(request->destaccnum(), request->srcaccnum(), request->trade_amount());

    response->set_status(res);
    response->set_message(msg);
    if (res)
    {
        unsigned int logid = std::stoi(msg);
        TransactionLog log = TransactionController::GetLogByLogId(logid);

        auto *log_entry = response->mutable_log();
        log_entry->set_logid(log.logId); // 로그 ID 설정
        log_entry->set_accnum(log.accNum);
        log_entry->set_userid(log.userId);
        log_entry->set_transaction_type(log.transaction_type);
        log_entry->set_trade_amount(log.trade_amount);
        log_entry->set_remaining_balance(log.remaining_balance);
        log_entry->set_created_at(log.created_at);
    }

    return grpc::Status();
}
