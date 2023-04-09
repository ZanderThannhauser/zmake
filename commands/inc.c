
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct commands* inc_commands(
	struct commands* this)
{
	return this->refcount++, this;
}

