#include "bank_database.h"

#include <random>
#include <string>
#include <vector>

#include "get_current_time.h"

namespace {
unsigned long long GenerateRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long long> distrib(100000000000, 999999999999);
    return distrib(gen);
}
} // namespace

AccountDB::AccountDB() : db(BankDatabase::getInstance()) { db->initStorage(); }

void AccountDB::MakeWithdrawLog(Account &targetAcc, unsigned int withdraw_money) {
    try {
        std::string createdAt = TimeStamp::get_current_time();
        db->getStorage().insert<TransactionLog>(
            TransactionLog{0, targetAcc.id, targetAcc.accId, targetAcc.cusId, 2, withdraw_money, targetAcc.balance, createdAt});
    } catch (std::exception &e) {
        db->handleException(e);
    }
}

void AccountDB::MakeDepositLog(Account &targetAcc, unsigned int deposit_money) {
    try {
        std::string createdAt = TimeStamp::get_current_time();
        db->getStorage().insert<TransactionLog>(
            TransactionLog{0, targetAcc.id, targetAcc.accId, targetAcc.cusId, 1, deposit_money, targetAcc.balance, createdAt});
    } catch (std::exception &e) {
        db->handleException(e);
    }
}

bool AccountDB::isExistAccId(std::string &accId) {
    try {
        return db->getStorage().count<Account>(where(c(&Account::accId) == accId));
    } catch (std::exception &e) {
        db->handleException(e);
    }
}

void AccountDB::CreateAccount(int cusId, int account_type) {
    try {
        std::string accId;
        accId = std::to_string(GenerateRandomNumber());

        // accId가 이미 존재하는지 확인
        if (!isExistAccId(accId)) {
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
            auto insertedAccount = db->getStorage().get<Account>(insertedId);

            // 조회된 계좌 정보 출력
            std::cout << "계좌가 성공적으로 생성되었습니다. 계좌 정보:" << std::endl;
            std::cout << "ID: " << insertedAccount.id << std::endl;
            std::cout << "계좌 번호: " << insertedAccount.accId << std::endl;
            std::cout << "고객 ID: " << insertedAccount.cusId << std::endl;
            std::cout << "잔액: " << insertedAccount.balance << std::endl;
            std::cout << "계좌 유형: " << insertedAccount.account_type << std::endl;
            std::cout << "활성화 상태: " << (insertedAccount.status ? "활성" : "비활성") << std::endl;
            std::cout << "생성 시간: " << insertedAccount.created_at << std::endl;
        } else {
            std::cout << "이미 존재하는 계좌 번호입니다." << std::endl;
        }
    } catch (std::exception &e) {
        db->handleException(e); // 예외 처리
    }
}

std::vector<Account> AccountDB::GetAccountsByCusId(int cusId) {
    try {
        std::vector<Account> ret = db->getStorage().get_all<Account>(where(c(&Account::cusId) == cusId));

        // 조회 결과가 비어있는 경우 빈 벡터 반환
        if (ret.empty()) {
            return {}; // 빈 벡터 반환
        }
        return ret;
    } catch (std::exception &e) {
        db->handleException(e);
    }
}

void AccountDB::DepositBalanceByAccId(std::string accId, unsigned int deposit_amount, int cusId) {
    try {
        auto accounts = db->getStorage().get_all<Account>(where(c(&Account::accId) == accId));

        // 조회된 계좌 정보 출력
        if (!accounts.empty()) {
            accounts[0].balance += deposit_amount;
            db->getStorage().update(accounts[0]);
            MakeDepositLog(accounts[0], deposit_amount);
        }
    } catch (std::system_error e) {
        // 계좌 못 찾음
    } catch (bool expn) {
        // 본인 계좌가 아님
    } catch (std::exception &e) {
        db->handleException(e);
    }
}

void AccountDB::WithdrawBalanceByAccId(std::string accId, unsigned int withdraw_amount, int cusId) {
    try {
        Account targetAcc = db->getStorage().get<Account>(where(c(&Account::accId) == accId));

        if (targetAcc.cusId != cusId)
            throw -1;

        if (targetAcc.balance < withdraw_amount) {
            throw false;
        }
        targetAcc.balance -= withdraw_amount;
        db->getStorage().update(targetAcc);
        MakeWithdrawLog(targetAcc, withdraw_amount);
    } catch (std::system_error e) {
        // 계좌 못 찾음
    } catch (int expn) {
        // 자기 계좌가 아님
    } catch (bool expn) {
        // 잔액 부족
    } catch (std::exception &e) {
        db->handleException(e);
    }
}

void AccountDB::UpdateAccount(Account &targetAcc) {
    try {
        db->getStorage().update(targetAcc);
    } catch (std::exception &e) {
        db->handleException(e);
    }
}

void AccountDB::DeleteAccount(std::string accId) {
    try {
        db->getStorage().remove<Account>(accId);
    } catch (std::exception &e) {
        db->handleException(e);
    }
}
