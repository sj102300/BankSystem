#include "customerdb.h"

class CustomerController{
public:
    static std::tuple<bool, Customer> SignUp(std::string userId, std::string password, std::string name);
    static std::tuple<bool, Customer> Login(std::string userId, std::string password);
};