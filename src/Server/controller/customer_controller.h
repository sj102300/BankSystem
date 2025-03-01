#include "customerdb.h"

class CustomerController{
public:
    static std::tuple<bool, std::string> SignUp(std::string userId, std::string password, std::string name);
    static std::tuple<bool, std::string> Login(std::string userId, std::string password);
    static Customer CustomerController::GetCustomerInfo(std::string userId);
};