
#include <stdbool.h>

struct commands;

bool commands_run(
	struct commands* this,
	int dirfd);
