#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include "customerdb.h"
#include "accountdb.h"

using namespace sqlite_orm;

struct Savings
{
	unsigned int accId;
	long long balance;
	double interestRate;

	static auto getTableDefinition()
	{
		return make_table(
			"Savings",
			make_column("accId", &Savings::accId, primary_key()),
			make_column("balance", &Savings::balance, default_value(0)),
			make_column("interestRate", &Savings::interestRate, default_value(0)),
			foreign_key(&Savings::accId).references(&Account::accId));
	}
};

class SavingsDB{
public:
	SavingsDB();
	static Savings CreateSavings(unsigned int accId, long long balance, double interestRate);
	static std::tuple<bool, Savings> GetSavings(unsigned int accId);
	static void UpdateSavings();
	static void DeleteSavings();
};