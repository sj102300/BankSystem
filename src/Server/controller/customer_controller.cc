
#include "customer_controller.h"

std::tuple<bool, std::string> CustomerController::SignUp(std::string userId, std::string password, std::string name){
    //중복 아이디인 경우
    if(CustomerDB::isExistUserId(userId)){
        return {false, "중복된 아이디입니다."};
    }

    //password 암호화하기
    Customer cus = CustomerDB::CreateCustomer(userId, password, name);
    return {true, "회원가입 성공"};
}

std::tuple<bool, std::string> CustomerController::Login(std::string userId, std::string password){

    const auto [available, cus] = CustomerDB::GetCustomerByUserId(userId);
    
    //아이디 조회 실패
    if(!available)
        return {false, "아이디가 없습니다."};
    
    //비밀번호 틀림
    if(cus.password != password)
        return {false, "비밀번호가 틀렸습니다."};
    
    return {true, "로그인 성공"};
}

Customer CustomerController::GetCustomerInfo(std::string userId){
    const auto [available, cus] = CustomerDB::GetCustomerByUserId(userId);
    return cus;
}