//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/planner.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/sql_statement.hpp"
#include "duckdb/planner/binder.hpp"
#include "duckdb/planner/bound_parameter_map.hpp"
#include "duckdb/planner/logical_operator.hpp"

namespace duckdb {
class ClientContext;
class PreparedStatementData;

//! The planner creates a logical query plan from the parsed SQL statements
//! using the Binder and LogicalPlanGenerator.
class Planner {
	friend class Binder;

	// Planner 负责将AST的SQLStatement转换为未经优化的LogicalPlan
public:
	// Planner需要一个ClientContext来进行构造
	// 因为ClientContext本身就encapsulates all related information
	explicit Planner(ClientContext &context);

public:
	// 每个节点都是一个LogicalOperator
	// 根节点代表整个logical plan
	unique_ptr<LogicalOperator> plan;
	vector<string> names;
	// operator输出的output schema
	vector<LogicalType> types;
	case_insensitive_map_t<BoundParameterData> parameter_data;

	shared_ptr<Binder> binder;
	ClientContext &context;

	StatementProperties properties;
	bound_parameter_map_t value_map;

public:
	void CreatePlan(unique_ptr<SQLStatement> statement);
	static void VerifyPlan(ClientContext &context, unique_ptr<LogicalOperator> &op,
	                       optional_ptr<bound_parameter_map_t> map = nullptr);

private:
	void CreatePlan(SQLStatement &statement);
	shared_ptr<PreparedStatementData> PrepareSQLStatement(unique_ptr<SQLStatement> statement);
};
} // namespace duckdb
