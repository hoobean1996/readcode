# Query Optimizer

- `Value`
- `LogicalOperator`
- `LogicalOperatorVisitor`
- `ExpressionRewriter`
- `Rule`
  - `DatePartSimplificationRule`: data_part('year', x) => year(x)
  - `ComparisonSimplificationRule`: x = NULL => NULL
