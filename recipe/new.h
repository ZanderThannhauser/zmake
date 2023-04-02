
struct zebu_commands;
struct dirfd;

struct recipe* new_recipe(
	char* target,
	struct dirfd* dirfd,
	struct zebu_commands* commands);
