//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/optimizer_type.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/common/constants.hpp"
#include "duckdb/common/vector.hpp"

namespace duckdb {

// OptimizerType 我们有很多种优化类型

enum class OptimizerType : uint32_t {
	INVALID = 0,
	// age + 5 > 30 -> age > 25 (const folding)
	// SELECT * FROM table WHERE col1 > 10 AND col2 < 20 (predicate pushdown)
	// SELECT col1 + col2, (col1 + col2) * 2 FROM table (common subexpression elimination)
	// WHERE col IS NOT NULL AND col > 10 -> WHERE col > 10 (if col is not null) (null check elimination)
	// WHERE (a AND b) OR (a AND c) -> WHERE a AND (b OR c) (boolean expression simplification)
	// WHERE UPPER(name) = 'JOHN', (function inlining)
	// type casting
	// case expression
	// arithmetic simplification
	// join condition rewriting
	EXPRESSION_REWRITER,

	// FILTER_PULLUP 和 predicate pushdown 是相反的
	// filter(a > 10) -> filter(b < 20) -> filter (a > 10 and b < 20)
	FILTER_PULLUP,
	// predicate pushdown ~= filter pushdown
	// predicate pushdown refers to WHERE clause,
	FILTER_PUSHDOWN,
	// WITH cte AS (SELECT * FROM large_table)
	// SELECT * FROM cte WHERE some_column > 10

	// WITH cte AS (SELECT * FROM large_table WHERE some_column > 10)
	// SELECT * FROM cte
	CTE_FILTER_PUSHER,
	// to optimize quries that use regular expressions
	// SELECT * FROM table WHERE column REXGEXP '^[a-f]'
	// SELECT * FROM talbe WHERE column >= 'a' AND column < 'g'
	REGEX_RANGE,
	//
	IN_CLAUSE,
	JOIN_ORDER,
	DELIMINATOR,
	UNNEST_REWRITER,
	UNUSED_COLUMNS,
	STATISTICS_PROPAGATION,
	COMMON_SUBEXPRESSIONS,
	COMMON_AGGREGATE,
	COLUMN_LIFETIME,
	BUILD_SIDE_PROBE_SIDE,
	LIMIT_PUSHDOWN,
	TOP_N,
	COMPRESSED_MATERIALIZATION,
	DUPLICATE_GROUPS,
	REORDER_FILTER,
	JOIN_FILTER_PUSHDOWN,
	EXTENSION
};

string OptimizerTypeToString(OptimizerType type);
OptimizerType OptimizerTypeFromString(const string &str);
vector<string> ListAllOptimizers();

} // namespace duckdb
