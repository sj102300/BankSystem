#pragma once

namespace BankSystem
{
    class ATM
    {
    public:
        static void Welcome();
        static const int Exit();
        static const int Login();
        static const int Signup();

        static void CustomerVisit(int cusId);
        static int GetOptionCode();
        static bool MakeAccount(int cusId);
        static bool Deposit(int cusId);
        static bool Withdraw(int cusId);
        static bool PrintAccountInfo(int cusId);
        static bool CustomerLeave(int cusId);
    };
} // namespace BankSystem