//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/query_node.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/common/common.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/common/insertion_order_preserving_map.hpp"
#include "duckdb/parser/common_table_expression_info.hpp"
#include "duckdb/parser/parsed_expression.hpp"
#include "duckdb/parser/result_modifier.hpp"

namespace duckdb {

class Deserializer;
class Serializer;

enum class QueryNodeType : uint8_t {
	SELECT_NODE = 1,         // SELECT Query
	SET_OPERATION_NODE = 2,  // UNION, INTERSECT, EXCEPT
	BOUND_SUBQUERY_NODE = 3, // Sub Query
	RECURSIVE_CTE_NODE = 4,  // Recursive CTE
	CTE_NODE = 5             // CTE
};

struct CommonTableExpressionInfo;

class CommonTableExpressionMap {
public:
	CommonTableExpressionMap();

	InsertionOrderPreservingMap<unique_ptr<CommonTableExpressionInfo>> map;

public:
	string ToString() const;
	CommonTableExpressionMap Copy() const;

	void Serialize(Serializer &serializer) const;
	// static void Deserialize(Deserializer &deserializer, CommonTableExpressionMap &ret);
	static CommonTableExpressionMap Deserialize(Deserializer &deserializer);
};

class QueryNode {
public:
	explicit QueryNode(QueryNodeType type) : type(type) {
	}
	virtual ~QueryNode() {
	}

	//! The type of the query node, either SetOperation or Select
	QueryNodeType type;
	//! The set of result modifiers associated with this query node
	vector<unique_ptr<ResultModifier>> modifiers;
	//! CTEs (used by SelectNode and SetOperationNode)
	CommonTableExpressionMap cte_map;

	virtual const vector<unique_ptr<ParsedExpression>> &GetSelectList() const = 0;

public:
	//! Convert the query node to a string
	virtual string ToString() const = 0;

	virtual bool Equals(const QueryNode *other) const;

	//! Create a copy of this QueryNode
	virtual unique_ptr<QueryNode> Copy() const = 0;

	string ResultModifiersToString() const;

	//! Adds a distinct modifier to the query node
	void AddDistinct();

	virtual void Serialize(Serializer &serializer) const;
	static unique_ptr<QueryNode> Deserialize(Deserializer &deserializer);

protected:
	//! Copy base QueryNode properties from another expression to this one,
	//! used in Copy method
	void CopyProperties(QueryNode &other) const;

public:
	template <class TARGET>
	TARGET &Cast() {
		if (type != TARGET::TYPE) {
			throw InternalException("Failed to cast query node to type - query node type mismatch");
		}
		return reinterpret_cast<TARGET &>(*this);
	}

	template <class TARGET>
	const TARGET &Cast() const {
		if (type != TARGET::TYPE) {
			throw InternalException("Failed to cast query node to type - query node type mismatch");
		}
		return reinterpret_cast<const TARGET &>(*this);
	}
};

} // namespace duckdb
