
struct recipeset;
struct database;
struct dirfd;
struct scope;

void parse(
	struct recipeset* all_recipes,
	struct database* database,
	struct dirfd* dirfd,
	struct scope* scope,
	const char* path);
