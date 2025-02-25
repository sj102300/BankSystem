
#include <string>

namespace customer{
    typedef struct _customerInfo{
        const unsigned int cusId;     //db auto increment
        const std::string userId;   //로그인 아이디
        std::string password; //로그인 비밀번호
        std::string name;    
        std::string createdAt;  
    } CustomerInfo;
}