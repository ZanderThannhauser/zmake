
struct zebu_postfix_expression;
struct scope;

struct value* evaluate_postfix_expression(
	struct zebu_postfix_expression* expression,
	struct scope* scope);
