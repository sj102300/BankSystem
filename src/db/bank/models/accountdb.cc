#include <random>
#include <string>
#include <vector>

#include "bank_database.h"
#include "get_current_time.h"

namespace
{
    unsigned long long GenerateRandomNumber()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<unsigned long long> distrib(100000000000,
                                                                  999999999999);
        return distrib(gen);
    }
} // namespace

AccountDB::AccountDB() {}

void AccountDB::MakeWithdrawLog(Account &targetAcc,
                                unsigned int withdraw_money)
{
    BankDatabase *db = BankDatabase::getInstance();
    try
    {
        std::string createdAt = TimeStamp::get_current_time();
        db->getStorage().insert<TransactionLog>(
            TransactionLog{0, targetAcc.id, targetAcc.accId, targetAcc.cusId, 2,
                           withdraw_money, targetAcc.balance, createdAt});
    }
    catch (std::exception &e)
    {
        db->handleException(e);
    }
}

void AccountDB::MakeDepositLog(Account &targetAcc, unsigned int deposit_money)
{
    BankDatabase *db = BankDatabase::getInstance();
    try
    {
        std::string createdAt = TimeStamp::get_current_time();
        db->getStorage().insert<TransactionLog>(
            TransactionLog{0, targetAcc.id, targetAcc.accId, targetAcc.cusId, 1,
                           deposit_money, targetAcc.balance, createdAt});
    }
    catch (std::exception &e)
    {
        db->handleException(e);
    }
}

bool AccountDB::isExistAccId(std::string &accId)
{
    BankDatabase *db = BankDatabase::getInstance();
    try
    {
        return db->getStorage().count<Account>(where(c(&Account::accId) == accId));
    }
    catch (std::exception &e)
    {
        db->handleException(e);
    }
}

Account AccountDB::CreateAccount(int cusId, unsigned int account_type)
{
    BankDatabase *db = BankDatabase::getInstance();
    try
    {
        // db에 없는 새로운 계좌번호 생성
        std::string accId;
        do
        {
            accId = std::to_string(GenerateRandomNumber());
        } while (isExistAccId(accId));

        // 현재 시간을 string으로 변환
        std::string createdAt = TimeStamp::get_current_time();

        // Account 객체 생성 및 데이터베이스에 삽입
        int insertedId = db->getStorage().insert(Account{
            0,            // id (자동 생성)
            accId,        // 계좌 ID
            cusId,        // 고객 ID
            0,            // 초기 잔액
            account_type, // 계좌 유형
            true,         // 활성화 상태
            createdAt     // 생성 시간
        });

        // 삽입된 계좌 정보를 데이터베이스에서 조회
        Account insertedAccount = db->getStorage().get<Account>(insertedId);
        return insertedAccount;
    }
    catch (std::exception &e)
    {
        db->handleException(e); // 예외 처리
    }
}

std::vector<Account> AccountDB::GetAccountsByCusId(int cusId)
{
    BankDatabase *db = BankDatabase::getInstance();

    try
    {
        std::vector<Account> ret =
            db->getStorage().get_all<Account>(where(c(&Account::cusId) == cusId));

        // 조회 결과가 비어있는 경우 빈 벡터 반환
        if (ret.empty())
            return {};

        return ret;
    }
    catch (std::exception &e)
    {
        db->handleException(e);
    }
}

bool AccountDB::DepositBalanceByAccId(std::string &accId,
                                      unsigned int deposit_amount, int cusId)
{
    BankDatabase *db = BankDatabase::getInstance();
    try
    {
        auto accounts =
            db->getStorage().get_all<Account>(where(c(&Account::accId) == accId));

        // 조회할 계좌가 없음. 입금 실패
        if (accounts.empty())
            return false;

        if (accounts[0].cusId != cusId)
            return false; // 권한없음. 입금 실패

        accounts[0].balance += deposit_amount;
        db->getStorage().update(accounts[0]);
        MakeDepositLog(accounts[0], deposit_amount);
        return true;
    }
    catch (std::exception &e)
    {
        db->handleException(e);
    }
}

bool AccountDB::WithdrawBalanceByAccId(std::string &accId,
                                       unsigned int withdraw_amount,
                                       int cusId)
{
    BankDatabase *db = BankDatabase::getInstance();
    try
    {
        auto targetAcc =
            db->getStorage().get_all<Account>(where(c(&Account::accId) == accId));

        if (targetAcc.empty())
            return false; // 계좌 조회 실패. 출금 실패.

        if (targetAcc[0].balance < withdraw_amount)
            return false; // 잔액 부족. 출금 실패

        if (targetAcc[0].cusId != cusId)
            return false; // 권한 없음. 출금 실패

        targetAcc[0].balance -= withdraw_amount;
        db->getStorage().update(targetAcc[0]);
        MakeWithdrawLog(targetAcc[0], withdraw_amount);
        return true;
    }
    catch (std::exception &e)
    {
        db->handleException(e);
    }
}

void AccountDB::UpdateAccount(Account &targetAcc)
{
    BankDatabase *db = BankDatabase::getInstance();
    try
    {
        db->getStorage().update(targetAcc);
    }
    catch (std::exception &e)
    {
        db->handleException(e);
    }
}

void AccountDB::DeleteAccount(std::string accId)
{
    // transaction 외래키와의 종속성 때문에
    // 그냥 remove안하고 계좌 status를 false로
    BankDatabase *db = BankDatabase::getInstance();
    try
    {
        auto targetAcc = db->getStorage().get_all<Account>(where(c(&Account::accId) == accId));

        if (targetAcc.empty())
            return; // 삭제할 계좌 없음.

        targetAcc[0].status = false;
        db->getStorage().update(targetAcc[0]);
    }
    catch (std::exception &e)
    {
        db->handleException(e);
    }
}
