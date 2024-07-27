//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/optimizer/optimizer.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/common/enums/optimizer_type.hpp"
#include "duckdb/optimizer/expression_rewriter.hpp"
#include "duckdb/planner/logical_operator.hpp"
#include "duckdb/planner/logical_operator_visitor.hpp"

#include <functional>

namespace duckdb {
class Binder;

class Optimizer {
public:
	// Optimizer 接受一个Binder
	Optimizer(Binder &binder, ClientContext &context);

	//! Optimize a plan by running specialized optimizers
	// 对给定的Plan进行优化
	unique_ptr<LogicalOperator> Optimize(unique_ptr<LogicalOperator> plan);
	//! Return a reference to the client context of this optimizer
	ClientContext &GetContext();
	//! Whether the specific optimizer is disabled
	bool OptimizerDisabled(OptimizerType type);

public:
	ClientContext &context;
	Binder &binder;
	ExpressionRewriter rewriter;

private:
	void RunBuiltInOptimizers();
	void RunOptimizer(OptimizerType type, const std::function<void()> &callback);
	void Verify(LogicalOperator &op);

private:
	unique_ptr<LogicalOperator> plan;
};

} // namespace duckdb
