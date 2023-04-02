
#include <stdlib.h>
#include <unistd.h>
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_dirfd(
	struct dirfd* this)
{
	if (this && !--this->refcount)
	{
		close(this->fd);
		free(this);
	}
}

