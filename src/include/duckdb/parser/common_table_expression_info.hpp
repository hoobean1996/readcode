//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/common_table_expression_info.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/common/enums/cte_materialize.hpp"
#include "duckdb/parser/statement/select_statement.hpp"

namespace duckdb {

class SelectStatement;

// CommonTableExpressionInfo
// Common Table Expression.
// CTE are named temporary results sets that you can reference within a SELECT

// WITH clause 允许我们指定一个Common Table Expression.
/*
    WITH cte AS (SELECT 42 AS X)
    SELECT * FROM cte
*/
struct CommonTableExpressionInfo {
	vector<string> aliases;
	unique_ptr<SelectStatement> query;
	CTEMaterialize materialized = CTEMaterialize::CTE_MATERIALIZE_DEFAULT;

	void Serialize(Serializer &serializer) const;
	static unique_ptr<CommonTableExpressionInfo> Deserialize(Deserializer &deserializer);
	unique_ptr<CommonTableExpressionInfo> Copy();
};

} // namespace duckdb
