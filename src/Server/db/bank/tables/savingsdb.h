#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include "customerdb.h"
#include "accountdb.h"

using namespace sqlite_orm;

struct Savings
{
	std::string accNum;
	long long balance;
	double interestRate;

	static auto getTableDefinition()
	{
		return make_table(
			"Savings",
			make_column("accNum", &Savings::accNum, primary_key()),
			make_column("balance", &Savings::balance, default_value(0)),
			make_column("interestRate", &Savings::interestRate, default_value(0)),
			foreign_key(&Savings::accNum).references(&Account::accId));
	}
};

class SavingsDB{
public:
	SavingsDB();
	static Savings CreateSavings(std::string accNum, double interestRate);
	static std::tuple<bool, Savings> GetSavings(std::string accNum);
	static void UpdateSavings(Savings& savings);
	static void DeleteSavings();
};