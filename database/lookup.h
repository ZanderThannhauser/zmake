
struct database;
struct dirfd;

time_t database_lookup(
	struct database* database,
	const char* target,
	struct dirfd* dirfd);
