
struct zebu_statement;
struct zebu_statements;
struct recipeset;
struct database;
struct dirfd;
struct scope;

void evaluate_statements(
	struct zebu_statements* statements,
	struct recipeset* all_recipes,
	struct recipeset* propagate_ftimes,
	struct database* database,
	struct dirfd* absolute_dirfd,
	struct dirfd* local_dirfd,
	struct scope* scope);
	
