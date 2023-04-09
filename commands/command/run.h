
#include <stdbool.h>

struct command;

bool command_run(
	struct command* this,
	int dirfd);
