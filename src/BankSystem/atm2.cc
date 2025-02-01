#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "atm.h"
#include "bank/bank_database.h"
#include "common_option.h"

namespace BankSystem {

int ATM::GetOptionCode() {
    int option;
    std::cout << "-----Menu-----" << std::endl;
    std::cout << "1. 계좌개설" << std::endl;
    std::cout << "2. 입 금" << std::endl;
    std::cout << "3. 출 금" << std::endl;
    std::cout << "4. 계좌정보 전체 출력" << std::endl;
    std::cout << "5. 프로그램 종료" << std::endl;
    std::cout << "선택: ";
    std::cin >> option;
    std::cout << "-------------" << std::endl;
    return option;
}

void ATM::CustomerVisit(int cusId) {
    int option = 0;
    while (option != 5) {
        option = GetOptionCode();
        switch (option) {
        case (Bank_Option::MAKE):
            MakeAccount(cusId);
            break;
        case (Bank_Option::DEPOSIT):
            Deposit(cusId);
            break;
        case (Bank_Option::WITHDRAW):
            Withdraw(cusId);
            break;
        case (Bank_Option::INQUIRE):
            PrintAccountInfo(cusId);
            break;
        case (Bank_Option::EXIT):
            break;
        default:
            std::cout << "잘못된 입력입니다." << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "종료" << std::endl;
}

void ATM::MakeAccount(int cusId) {
    AccountDB accountdb;
    accountdb.CreateAccount(cusId, 1); // 일반 계좌는 1번...
    std::cout << "계좌 개설 완료" << std::endl;
}

void ATM::Deposit(int cusId) {
    AccountDB accountdb;
    std::string accId;
    std::cout << "입금할 계좌 번호를 입력해주세요: " << std::endl;
    while (true) {
        std::cin >> accId;
        if (accountdb.isExistAccId(accId)) {
            break;
        }
        std::cout << "잘못된 계좌입니다. 다시 입력해주세요" << std::endl;
    }

    int deposit_money;
    std::cout << "입금할 금액을 입력해주세요: " << std::endl;
    while (true) {
        std::cin >> deposit_money;
        if (deposit_money >= 0) {
            break;
        }
        std::cout << "잘못된 입력입니다. 다시 입력해주세요" << std::endl;
    }
    accountdb.DepositBalanceByAccId(accId, deposit_money, cusId);
}

void ATM::Withdraw(int cusId) {
    AccountDB accountdb;
    std::string accId;
    std::cout << "출금할 계좌 번호를 입력해주세요: " << std::endl;
    while (true) {
        std::cin >> accId;
        if (accountdb.isExistAccId(accId)) {
            break;
        }
        std::cout << "잘못된 계좌입니다. 다시 입력해주세요" << std::endl;
    }

    int withdraw_money;
    std::cout << "출금할 금액을 입력해주세요: " << std::endl;
    while (true) {
        std::cin >> withdraw_money;
        if (withdraw_money >= 0) {
            break;
        }
        std::cout << "잘못된 입력입니다. 다시 입력해주세요" << std::endl;
    }
    accountdb.DepositBalanceByAccId(accId, withdraw_money, cusId);
}

void ATM::PrintAccountInfo(int cusId) {
    AccountDB accountdb;
    std::vector<Account> accounts = accountdb.GetAccountsByCusId(cusId);

    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        std::cout << "계좌 번호: " << it->accId << std::endl;
        std::cout << "잔액: " << it->balance << std::endl;
        std::cout << "----------------------\n";
    }
}

void ATM::Welcome() {
    int cusId;
    CustomerDB customerdb;
    std::cout << "어서오세요 ATM입니다." << std::endl;

    int option = 0;

    while (true) {
        std::cout << "1. 고객 번호로 로그인" << std::endl;
        std::cout << "2. 회원 가입" << std::endl;
        std::cout << "0. 종료" << std::endl;

        std::cin >> option;

        if (option == 1) {
            int cusId;
            std::cout << "회원 번호를 입력해주세요: " << std::endl;
            std::cin >> cusId;
            if (customerdb.isExistByCusId(cusId)) {
                std::cout << "로그인 되었습니다." << std::endl;
                CustomerVisit(cusId);
                break;
            }
            std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
        } else if (option == 2) {
            std::string name;
            std::cout << "이름을 입력해주세요: " << std::endl;
            std::cin >> name;
            const auto cus_idx = customerdb.CreateCustomer(name);
            std::cout << "회원 가입이 완료되었습니다." << std::endl;

            int cusId = customerdb.GetCustomerId(cus_idx);
            std::cout << "회원 번호는 : " << cusId << std::endl;
            CustomerVisit(cusId);
            break;
        } else if (option == 0) {
            std::cout << "프로그램 종료" << std::endl;
            exit(1); // 강제종료....
        } else {
            std::cout << "잘못된 입력입니다. 다시 입력해주세요" << std::endl;
        }
    }
}

} // namespace BankSystem
