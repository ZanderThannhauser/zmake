
struct zebu_token;

struct value* evaluate_string_expression(
	struct zebu_token* token);

char* escape_zebu_string(
	struct zebu_token* token);
