//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/operator/logical_create.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/parsed_data/create_info.hpp"
#include "duckdb/planner/logical_operator.hpp"

namespace duckdb {

//! LogicalCreate represents a CREATE operator
// LogicalOperator is descriptive,
// only describe what should we do, it's abstract, database-agnostic way
class LogicalCreate : public LogicalOperator {
public:
	static constexpr const LogicalOperatorType TYPE = LogicalOperatorType::LOGICAL_INVALID;

public:
	LogicalCreate(LogicalOperatorType type, unique_ptr<CreateInfo> info,
	              optional_ptr<SchemaCatalogEntry> schema = nullptr);

	optional_ptr<SchemaCatalogEntry> schema;
	unique_ptr<CreateInfo> info;

public:
	void Serialize(Serializer &serializer) const override;
	static unique_ptr<LogicalOperator> Deserialize(Deserializer &deserializer);

	idx_t EstimateCardinality(ClientContext &context) override;

protected:
	void ResolveTypes() override;

private:
	LogicalCreate(LogicalOperatorType type, ClientContext &context, unique_ptr<CreateInfo> info);
};
} // namespace duckdb
