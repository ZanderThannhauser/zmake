
struct database;
struct dirfd;

void database_add_test_result(
	struct database* this,
	const char* target,
	struct dirfd* dirfd,
	bool passed);
