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
}

AccountDB::AccountDB() {
    db->initStorage();
}

void AccountDB::MakeWithdrawLog(Account& targetAcc, unsigned int withdraw_money) {
    try {
        std::string createdAt = TimeStamp::get_current_time();
        db->getStorage().insert<TransactionLog>(TransactionLog{
            0, targetAcc.id, targetAcc.accId, targetAcc.cusId, 2, withdraw_money, targetAcc.balance, createdAt
        });
    } catch (std::exception& e) {
        db->handleException(e);
    }
}

void AccountDB::MakeDepositLog(Account& targetAcc, unsigned int deposit_money) {
    try {
        std::string createdAt = TimeStamp::get_current_time();
        db->getStorage().insert<TransactionLog>(TransactionLog{
            0, targetAcc.id, targetAcc.accId, targetAcc.cusId, 1, deposit_money, targetAcc.balance, createdAt
        });
    } catch (std::exception& e) {
        db->handleException(e);
    }
}

bool AccountDB::isExistAccId(std::string& accId) {
    try {
        return db->getStorage().count<Account>(where(c(&Account::accId) == accId));
    } catch (std::exception& e) {
        db->handleException(e);
    }
}

void AccountDB::CreateAccount(int cusId, int account_type) {
    try {
        std::string accId;
        do {
            accId = std::to_string(GenerateRandomNumber());
        } while (!isExistAccId(accId));

        std::string createdAt = TimeStamp::get_current_time();
        db->getStorage().insert(Account{0, accId, cusId, 0, 1, true, createdAt});
    } catch (std::exception& e) {
        db->handleException(e);
    }
}

std::vector<Account> AccountDB::GetAccountsByCusId(int cusId) {
    try {
        std::vector<Account> ret = db->getStorage().get_all<Account>(cusId);
        return ret;
    } catch (std::exception& e) {
        db->handleException(e);
    }
}

void AccountDB::DepositBalanceByAccId(std::string accId, unsigned int deposit_amount, int cusId) {
    try {
        Account targetAcc = db->getStorage().get<Account>(where(c(&Account::accId) == accId));
        if(targetAcc.cusId != cusId)
            throw false;
        targetAcc.balance += deposit_amount;
        db->getStorage().update(targetAcc);
        MakeDepositLog(targetAcc, deposit_amount);
    } catch (std::system_error e) {
        // 계좌 못 찾음
    } catch(bool expn){
        //본인 계좌가 아님
    } catch (std::exception& e) {
        db->handleException(e);
    }
}

void AccountDB::WithdrawBalanceByAccId(std::string accId, unsigned int withdraw_amount, int cusId) {
    try {
        Account targetAcc = db->getStorage().get<Account>(where(c(&Account::accId) == accId));
        
        if(targetAcc.cusId != cusId)
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
    } catch (std::exception& e) {
        db->handleException(e);
    }
}

void AccountDB::UpdateAccount(Account& targetAcc) {
    try {
        db->getStorage().update(targetAcc);
    } catch (std::exception& e) {
        db->handleException(e);
    }
}

void AccountDB::DeleteAccount(std::string accId) {
    try {
        db->getStorage().remove<Account>(accId);
    } catch (std::exception& e) {
        db->handleException(e);
    }
}
