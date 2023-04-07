
struct zebu_equality_expression;
struct scope;

struct value* evaluate_equality_expression(
	struct zebu_equality_expression* expression,
	struct scope* scope);
