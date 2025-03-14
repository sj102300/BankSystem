#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include "customerdb.h"
#include "accountdb.h"
#include "account_namespace.h"

using namespace sqlite_orm;

struct FixedDeposit
{
	unsigned int fixedDepositId;
	std::string accNum;
	unsigned long long monthlyPayment;
	std::string duedate;

	static auto getTableDefinition()
	{
		return make_table(
			"FixedDeposit",
			make_column("fixedDepositId", &FixedDeposit::fixedDepositId, primary_key().autoincrement()),
			make_column("accNum", &FixedDeposit::accNum, unique()),
			make_column("monthlyPayment", &FixedDeposit::monthlyPayment),
			make_column("duedate", &FixedDeposit::duedate),
			foreign_key(&FixedDeposit::accNum).references(&Account::accNum));
	}
};

class FixedDepositDB{
public:
	FixedDepositDB();
	static FixedDeposit CreateFixedDeposit(std::string accNum, unsigned long long monthly_payment, std::string duedate);
	static std::tuple<bool, FixedDeposit> GetFixedDepositInfo(std::string accNum);
	static std::tuple<bool, account::FixedDepositImplInfo> GetFixedDepositImpl(std::string accNum);
	static void UpdateFixedDeposit();
	static void DeleteFixedDeposit();  //구현안할거임
};