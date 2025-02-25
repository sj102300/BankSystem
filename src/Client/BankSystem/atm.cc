#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include "atm.h"
#include "db/bank/bank_database.h"
#include "common_option.h"

using namespace BankSystem;

void ATM::Welcome()
{
    int cusId;
    std::cout << "어서오세요 ATM입니다." << std::endl;

    std::unordered_map<int, std::function<const int()>> commands = {
        {Login_Option::LOGIN, ATM::Login},
        {Login_Option::SIGNUP, ATM::Signup},
        {Login_Option::EXIT, ATM::Exit},
    };
    
    int option = 0;
    while (true)
    {
        std::cout << "1. 고객 번호로 로그인" << std::endl;
        std::cout << "2. 회원 가입" << std::endl;
        std::cout << "0. 종료" << std::endl;
        std::cin >> option;

        if(commands.find(option) != commands.end()){
            int cusId = commands[option]();
            CustomerVisit(cusId);
        }else
            std::cout<<"잘못된 입력입니다. 다시 입력해주세요"<<std::endl;
    }
}

const int ATM::Exit(){
    std::cout<<"프로그램 종료"<<std::endl;
    exit(1);
    return -1;
}

const int ATM::Login()
{
    int cusId;
    std::cout << "회원 번호를 입력해주세요: " << std::endl;
    while (true)
    {
        std::cin >> cusId;
        if (CustomerDB::isExistByCusId(cusId))
            break;
        std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
    }
    std::cout << "로그인 되었습니다." << std::endl;
    return cusId;
}

const int ATM::Signup()
{
    std::string name;
    std::cout << "이름을 입력해주세요: " << std::endl;
    std::cin >> name;
    const Customer insertedCus = CustomerDB::CreateCustomer(name);
    std::cout << "회원 가입이 완료되었습니다." << std::endl;

    std::cout << "회원 번호 : " << insertedCus.cusId << std::endl;
    std::cout << "이름 : " << insertedCus.cus_name << std::endl;
    return insertedCus.cusId;
}

void ATM::CustomerVisit(int cusId)
{
    std::unordered_map<int, std::function<bool(int)>> commands = {
        {Customer_Option::MAKE, MakeAccount},
        {Customer_Option::DEPOSIT, Deposit},
        {Customer_Option::WITHDRAW, Withdraw},
        {Customer_Option::INQUIRE, PrintAccountInfo},
        {Customer_Option::EXIT, CustomerLeave},
    };

    int option = 0;
    bool goNext = true;
    while (goNext)
    {
        option = GetOptionCode();
        if(commands.find(option) != commands.end()){
            goNext = commands[option](cusId);
        }
        else
            std::cout << "잘못된 입력입니다." << std::endl;
        std::cout << std::endl;
    }
    std::cout << "종료" << std::endl;
}

int ATM::GetOptionCode()
{
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

bool ATM::MakeAccount(int cusId)
{
    Account insertedAccount = AccountDB::CreateAccount(cusId, 1); // 일반 계좌는 1번...
    // 조회된 계좌 정보 출력
    std::cout << "계좌가 성공적으로 생성되었습니다. 계좌 정보:" << std::endl;
    std::cout << "ID: " << insertedAccount.id << std::endl;
    std::cout << "계좌 번호: " << insertedAccount.accId << std::endl;
    std::cout << "고객 ID: " << insertedAccount.cusId << std::endl;
    std::cout << "잔액: " << insertedAccount.balance << std::endl;
    std::cout << "계좌 유형: " << insertedAccount.account_type << std::endl;
    std::cout << "활성화 상태: "
              << (insertedAccount.status ? "활성" : "비활성") << std::endl;
    std::cout << "생성 시간: " << insertedAccount.created_at << std::endl;
    
    return true;
}

bool ATM::Deposit(int cusId)
{
    std::string accId;
    std::cout << "입금할 계좌 번호를 입력해주세요: " << std::endl;
    while (true)
    {
        std::cin >> accId;
        if (AccountDB::isExistAccId(accId))
            break;

        std::cout << "잘못된 계좌입니다. 다시 입력해주세요" << std::endl;
    }

    int deposit_money;
    std::cout << "입금할 금액을 입력해주세요: " << std::endl;
    while (true)
    {
        std::cin >> deposit_money;
        if (deposit_money >= 0)
            break;

        std::cout << "잘못된 입력입니다. 다시 입력해주세요" << std::endl;
    }

    if (AccountDB::DepositBalanceByAccId(accId, deposit_money, cusId))
        std::cout << "입금 성공" << std::endl;
    else
        std::cout << "입금 실패" << std::endl;
    return true;
}

bool ATM::Withdraw(int cusId)
{
    std::string accId;
    std::cout << "출금할 계좌 번호를 입력해주세요: " << std::endl;
    while (true)
    {
        std::cin >> accId;
        if (AccountDB::isExistAccId(accId))
            break;

        std::cout << "잘못된 계좌입니다. 다시 입력해주세요" << std::endl;
    }

    int withdraw_money;
    std::cout << "출금할 금액을 입력해주세요: " << std::endl;
    while (true)
    {
        std::cin >> withdraw_money;
        if (withdraw_money >= 0)
            break;

        std::cout << "잘못된 입력입니다. 다시 입력해주세요" << std::endl;
    }

    if (AccountDB::WithdrawBalanceByAccId(accId, withdraw_money, cusId))
        std::cout << "출금 성공" << std::endl;
    else
        std::cout << "출금 실패" << std::endl;
    
    return true;
}

bool ATM::PrintAccountInfo(int cusId)
{
    std::vector<Account> accounts = AccountDB::GetAccountsByCusId(cusId);

    for (auto it = accounts.begin(); it != accounts.end(); ++it)
    {
        std::cout << "계좌 번호: " << it->accId << std::endl;
        std::cout << "잔액: " << it->balance << std::endl;
        std::cout << "----------------------\n";
    }
    return true;
}

bool ATM::CustomerLeave(int cusId){
    return false;
}