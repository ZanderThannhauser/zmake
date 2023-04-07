
struct zebu_commands;
struct dirfd;

struct recipe* new_recipe(
	const char* target,
	struct dirfd* dirfd);
