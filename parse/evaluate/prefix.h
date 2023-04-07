
struct zebu_prefix_expression;
struct scope;

struct value* evaluate_prefix_expression(
	struct zebu_prefix_expression* expression,
	struct scope* scope);
