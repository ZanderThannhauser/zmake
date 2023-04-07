
struct zebu_primary_expression;
struct scope;

struct value* evaluate_primary_expression(
	struct zebu_primary_expression* expression,
	struct scope* scope);
