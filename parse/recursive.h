
void recursive_parse(
	struct database* database,
	struct recipeset* all_recipes,
	struct recipeset* propagate_ftimes,
	struct dirfd* absolute_dirfd,
	struct dirfd* local_dirfd,
	struct scope* scope,
	const char* path);
