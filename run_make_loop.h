
struct recipeset;
struct heap;
struct database;

void run_make_loop(
	int dirfd,
	struct recipeset* all_recipes,
	struct heap* ready,
	struct database* database);
