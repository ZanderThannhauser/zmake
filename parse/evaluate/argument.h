
struct zebu_argument;
struct scope;

void evaluate_argument(
	struct zebu_argument* argument,
	struct scope* scope,
	void (*callback)(char*));
