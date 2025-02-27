#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include "customerdb.h"
#include "accountdb.h"

using namespace sqlite_orm;

struct FixedDeposit
{
	unsigned int accId;
	unsigned long long monthlyPayment;
	std::string duedate;

	static auto getTableDefinition()
	{
		return make_table(
			"FixedDeposit",
			make_column("accId", &FixedDeposit::accId, primary_key()),
			make_column("monthlyPayment", &FixedDeposit::monthlyPayment),
			make_column("duedate", &FixedDeposit::duedate),
			foreign_key(&FixedDeposit::accId).references(&Account::accId));
	}
};

class FixedDepositDB{
public:
	FixedDepositDB();
	static FixedDeposit CreateFixedDeposit(unsigned int accId, unsigned long long monthly_payment, std::string duedate);
	static std::tuple<bool, FixedDeposit> GetFixedDeposit(unsigned int accId);
	static void UpdateFixedDeposit();
	static void DeleteFixedDeposit();  //구현안할거임
};