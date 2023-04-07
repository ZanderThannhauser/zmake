
struct zebu_relational_expression;
struct scope;

struct value* evaluate_relational_expression(
	struct zebu_relational_expression* expression,
	struct scope* scope);
