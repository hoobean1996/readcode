- overview of query processing
  - declarative
  - multiple alternatives
- overview of query optimization
- overview of query execution

## overview compile time system

- query
- parsing -> AST
- semantic analysis -> schema lookup, variable binding, type inferrence
- normalization, factorization, const folding
- rewrite : view resolution, unnesting, deriving predicates
- plan generation
- rewrite II
- code generation

## what to optimize

- minimize response time
- minimize resource consumption
- minimize time to first tuple
- maximize throughput

## basic goal of algbraic optimization

- find a cheaper / the chepeast expression that is equivenlent to the first one
  challeges:
- the set of possible expression is huge
- testing for equvilence is diffcult / impossible in general
- the query is given in a calculus and not an algebra
- simpler optimization problems are typically NP hard in general (join ordering)

## approach

- constructive
- ransofmative

## Relational Algebra

- A(e) attributes of the tuple produces by e
- F(e) free variables of the expression e
- binary operator e1 op e2 usually require A(e1) = A(e2)

- e1 union e2
- e1 intersect e2
- e1 difference e2
- rename
- projection
- product
- selection
- join

## physical algebra

- relational algebra does not imply an implementation
- the implementation can have a great impact
- therefore more detailed operators
- additional operators needed to be stream nature

Enforcer:

- somer operators do not affect the logical result but guarantee desired properties

  - sort
  - temp (materilize the input stream, make further read cheap)
  - ship (send the input stream to a different host)

- joins

  - nested loop join: reads all of e2 for every tuple of e1, very slow, but supports all kinds of predicates
  - blockwise nested loop join: read chunks of e1 into memory, and read e2 once for each chunk, much faster, but requires memory, furthre improvement: use hashing for equi-joins
  - sort merge join: scan e1 and e2 only once, but requires suitable sorted input, equi-join only
  - hybrid-hash join: partitions e1 and e2 into partitions that can be joined in memory, equi-join only

- aggregation
  - aggregate sorted input: aggregates the input directly, trivial and fast, but requires sorted input
  - aggregate quick sort: sort chunks of input with quicksort, merge sorts
  - aggregate heap sort: slower sort, but longer runs

## vs

- logical algebras describe only the general approach
- physical algebra fixes the eaxct execution including runtme characteristics
- multiple physical operators possible for a single logical operator
- query optimizer must produce physical algebra
- opeartor selection is a crucial step during optimization

## Textbook Query Optimization

- correctness is critical for query optimization
- can be only guaranteed by a formal model

- Tuple: a unordered mapping from attribute name to values of a domain
- Schema: a set of attributes with domain: {(name,string), (age: number)}
- Tuple Concatenation
- Tuple Projection
- Relations: a set of tuples with the same Schema
  - Relations are sets of tuples
  - Real data is usually a multi set (Bag)

the optimizer must consider these different semantics:

- logical algebra operates on bags
- physical algebra operats on streams (order matters)
- explicit duplicate elimination => sets

- Set Operations
- Free Variable: age = 62 (age is free varaible)
- Product
- Projection
- Selection
- Equivalences: a lot of formulas for transformation

## Canonical Query Translation

select distinct a1, ... ,an
from R1, ... Rk
where p

1. From Clause: translate the from clause
   F = R1 if k = 1 else F = (((R1 x R2) x R3) ...) x Rk

2. Where Clause: translate the where clause
   W = F if no where else construct P

3. Select Clause: translate the select clause
   S = W if pojection is \* else construct W

## Optimization Phases

- translate the query to canonical algebraic expression
- perform logical query opt
- perform physical query opt

## Concept of Logical Query Optimization

foundation: based on algebric equivalences
algebric equivalences span the potential search space

perform logicla query optimizatio:

- plans can be compared if there is a cost function
- cost functions need details that are not available when only considering logical algebra
- consequence: logical query optimization remains a heuristic

## Phases of Logical Query Optimization

1. break up conjunctive selection predicates
2. push selections down: push down those selection predicates to reduce tuples early
3. introduce joins: joins are cheapers than cross products
   SELECT e.Name, d.Name
   FROM Employees e
   JOIN Departments d ON e.ID = d.ID
   // above is better
   SELECT e.Name, d.Name
   FROM Employees e, Departments d
   WHERE e.ID = d.ID
4. determine join order: NP Hard
5. introduce and push down projection

## Phases of Physical Query Optimization

- add more execution information to the plan
- allow for cost calculations
- select index structures/access paths
- choose operator implementations
- add property enforce
- choose when to matierialize

1. Access Paths Selection

- scan + selection could be done by an index lookup
- multiple indices to choose from
- table scan might be the best, even if an index is available
- depends on selectivity, rule of thumb: 10%
- details statictis and cost required
- related problem: materizied views

2. Operator Selection
3. Property Enforcer

## Join Ordering

## Join Order

Concentrate on Join Order that is:

- conjunctive queries
- simple predicates
- predicates have the form a1 = a2 where a1 is an attribute and a2 is either an attribute or a constant
- even ignore constants in some algorithms

We join Relations Ri, Ri can be

- a base relation
- a base relation including selection
- a more complex building block or access path

- Basics
- Search Space
- Greedy Heuristics
- IKKBZ
- MVP
- Dynamic Programming
- Simplifying the Query Graph
- Generating Permutations
- Transformative Approaches
- Randomized Approaches
- Metaheuristics
- Iterative Dynamic Programming
- Ordering Preserving Joins

- Query Graph: Queries of this type can be characterized as Query Graph
  - chains
  - cycles
  - starts
  - cliques (every nodes connect)
  - cyclic (there is a cycle)
  - tree
  - grid

Join Tree:
a join tree is a binary tree with

- join operators as inner nodes
- relations as leaf nodes

## Join Selectivity

Input:
-Cardinality |Ri|

- f[i][j] if p[i][j] is the join predicate between Ri and Rj, define f[i][j] = |Ri p[i][j] Rj| / Ri x Rj

- given a join tree T, the cost function is defined as
  Cout(T) = if T is leaf then R else |T| + Cout(T1) + Cout(T2)

cost differs vastly between join trees,
different cost functions result in different costs
the cheapst plan is always the same here, but relative order varies
join tree with cross product are expensive

but when one relation cardinality is small, cross product is best

## Classification of Join Ordering Problems

- query graph class: chain, cycle, star, clique
- join tree structure: left-deep, zig-zag, bushy tree
- join construction: with cross products or without cross products
  - number of join trees with cross products grows exponentially
- cost functions: with or without ASI property

4 x 3 x 2 x 2 => totaly 48 different kinds of Join Order problems.


Catalan Number: the number of binary tree with n nodes C(n) = 1/n+1 (2n n)

## Chain Query + no Cross Products
