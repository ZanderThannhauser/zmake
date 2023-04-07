
struct zebu_iterative;
struct scope;

void evaluate_iterative_statement(
	struct zebu_iterative* iterative,
	struct recipeset* all_recipes,
	struct recipeset* propagate_ftimes,
	struct database* database,
	struct dirfd* absolute_dirfd,
	struct dirfd* local_dirfd,
	struct scope* scope);
