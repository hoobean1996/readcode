Here's a markdown list of the optimizations with their pros and examples:
Query Optimization Techniques
EXPRESSION_REWRITER

Pros: Simplifies expressions, reduces computational overhead
Example:
sqlCopy# Before
WHERE age + 5 > 30

# After

WHERE age > 25

FILTER_PULLUP

Pros: Combines multiple filters, enables better join optimizations
Example:
sqlCopy# Before
Filter(A > 10) -> Filter(B < 20) -> TableScan

# After

Filter(A > 10 AND B < 20) -> TableScan

FILTER_PUSHDOWN

Pros: Reduces data processed early, improves I/O efficiency
Example:
sqlCopy# Before
SELECT \* FROM table WHERE col1 > 10

# After

[Apply col1 > 10 filter during table scan]

CTE_FILTER_PUSHER

Pros: Reduces data processed in CTEs, improves overall query performance
Example:
sqlCopy# Before
WITH cte AS (SELECT _ FROM large_table)
SELECT _ FROM cte WHERE some_column > 10

# After

WITH cte AS (SELECT _ FROM large_table WHERE some_column > 10)
SELECT _ FROM cte

REGEX_RANGE

Pros: Converts regex to range comparisons, allows index usage
Example:
sqlCopy# Before
SELECT \* FROM table WHERE column REGEXP '^[a-f]'

# After

SELECT \* FROM table WHERE column >= 'a' AND column < 'g'

IN_CLAUSE

Pros: Optimizes IN clause queries, improves performance for large value lists
Example:
sqlCopy# Before
WHERE id IN (1, 2, 3, 4, 5)

# After

WHERE id BETWEEN 1 AND 5

JOIN_ORDER

Pros: Optimizes the order of joins for better performance
Example: Reordering joins based on table sizes and join conditions

UNNEST_REWRITER

Pros: Optimizes queries with unnest operations
Example: Transforming unnest operations for more efficient execution

UNUSED_COLUMNS

Pros: Eliminates processing of unnecessary columns
Example: Removing unused columns from intermediate results

STATISTICS_PROPAGATION

Pros: Improves cost estimation for query planning
Example: Propagating table statistics through query plans

COMMON_SUBEXPRESSIONS

Pros: Avoids redundant computations
Example: Computing a common expression once and reusing the result

COMMON_AGGREGATE

Pros: Optimizes queries with common aggregations
Example: Combining similar aggregate functions

COLUMN_LIFETIME

Pros: Optimizes memory usage by tracking column lifetimes
Example: Early disposal of columns no longer needed in query execution

BUILD_SIDE_PROBE_SIDE

Pros: Optimizes hash join performance
Example: Choosing optimal build and probe sides for hash joins

LIMIT_PUSHDOWN

Pros: Reduces data processed by pushing down LIMIT clauses
Example: Applying LIMIT early in the query execution plan

TOP_N

Pros: Optimizes queries requiring only top N results
Example: Efficient processing of ORDER BY ... LIMIT queries

COMPRESSED_MATERIALIZATION

Pros: Reduces memory usage for intermediate results
Example: Storing intermediate results in compressed format

DUPLICATE_GROUPS

Pros: Eliminates redundant grouping operations
Example: Removing unnecessary GROUP BY clauses

REORDER_FILTER

Pros: Optimizes the order of filter application
Example: Applying most selective filters first

JOIN_FILTER_PUSHDOWN

Pros: Pushes filters from joins down to table scans
Example: Moving join conditions into table scans where possible

EXTENSION

Pros: Allows for custom optimization rules
Example: Database-specific or user-defined optimization strategies
