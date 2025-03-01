
#include "customer_controller.h"

std::tuple<bool, Customer> CustomerController::SignUp(std::string userId, std::string password, std::string name){
    //중복 아이디인 경우
    if(CustomerDB::isExistUserId(userId)){
        return {false, {}};
    }

    //password 암호화하기
    Customer cus = CustomerDB::CreateCustomer(userId, password, name);
    return {true, cus};
}

std::tuple<bool, Customer> CustomerController::Login(std::string userId, std::string password){

    const auto [available, cus] = CustomerDB::GetCustomerByUserId(userId);
    
    //아이디 조회 실패
    if(!available)
        return {false, {}};
    
    //비밀번호 틀림
    if(cus.password != password)
        return {false, {}};
    
    return {true, cus};
}