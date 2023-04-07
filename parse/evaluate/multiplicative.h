
struct zebu_multiplicative_expression;
struct scope;

struct value* evaluate_multiplicative_expression(
	struct zebu_multiplicative_expression* expression,
	struct scope* scope);
