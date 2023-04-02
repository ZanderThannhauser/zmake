
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct dirfd* inc_dirfd(
	struct dirfd* this)
{
	return this->refcount++, this;
}

