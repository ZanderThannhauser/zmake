
struct zebu_expression;
struct scope;

struct value* evaluate_expression(
	struct zebu_expression* expression,
	struct scope* scope);
