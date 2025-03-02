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

Account AccountDB::CreateAccount(std::string userId, unsigned int account_type)
{
    BankDatabase *db = BankDatabase::getInstance();
    // db에 없는 새로운 계좌번호 생성
    std::string accNum;
    do
    {
        accNum = std::to_string(GenerateRandomNumber());
    } while (isExistAccNum(accNum));

    // 현재 시간을 string으로 변환
    std::string createdAt = TimeStamp::get_current_time();

    // Account 객체 생성 및 데이터베이스에 삽입
    int insertedId = db->getStorage().insert(Account{
        0,            // id (자동 생성)
        accNum,        // 계좌 ID
        userId,        // 고객 ID
        account_type, // 계좌 유형
        true,         // 활성화 상태
        createdAt     // 생성 시간
    });

    // 삽입된 계좌 정보를 데이터베이스에서 조회
    Account insertedAccount = db->getStorage().get<Account>(insertedId);
    return insertedAccount;
}

bool AccountDB::isExistAccNum(std::string &accNum)
{
    BankDatabase *db = BankDatabase::getInstance();
    return db->getStorage().count<Account>(where(c(&Account::accNum) == accNum));
}

std::vector<Account> AccountDB::GetAccountsByUserId(std::string userId)
{
    BankDatabase *db = BankDatabase::getInstance();

    std::vector<Account> ret =
        db->getStorage().get_all<Account>(where(c(&Account::userId) == userId));

    // 조회 결과가 비어있는 경우 빈 벡터 반환
    if (ret.empty())
        return {};

    return ret;
}

std::tuple<bool, Account> AccountDB::GetAccountByAccNum(std::string accNum)
{
    BankDatabase *db = BankDatabase::getInstance();
    

    std::vector<Account> ret =
        db->getStorage().get_all<Account>(where(c(&Account::accNum) == accNum));

    if (ret.empty())
        return {false, {}};

    return {true, ret.at(0)};

}

void AccountDB::UpdateAccount(Account &targetAcc)
{
    BankDatabase *db = BankDatabase::getInstance();
    db->getStorage().update(targetAcc);
}

void AccountDB::DeleteAccount(std::string accNum)
{
    // transaction 외래키와의 종속성 때문에
    // 그냥 remove안하고 계좌 status를 false로
    BankDatabase *db = BankDatabase::getInstance();
    auto targetAcc = db->getStorage().get_all<Account>(where(c(&Account::accNum) == accNum));

    if (targetAcc.empty())
        return; // 삭제할 계좌 없음.

    targetAcc[0].status = false;
    db->getStorage().update(targetAcc[0]);
}
