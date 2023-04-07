
struct scope;
struct zebu_additive_expression;

struct value* perform_add(
	struct value* left,
	struct value* right);

struct value* perform_subtract(
	struct value* left,
	struct value* right);

struct value* evaluate_additive_expression(
	struct zebu_additive_expression* expression,
	struct scope* scope);
