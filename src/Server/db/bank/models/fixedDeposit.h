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
			make_column("accId", &FixedDeposit::accId, primary_key().autoincrement()),
			make_column("monthlyPayment", &FixedDeposit::monthlyPayment),
			make_column("duedate", &FixedDeposit::duedate),
			foreign_key(&FixedDeposit::accId).references(&Account::accId));
	}
};
