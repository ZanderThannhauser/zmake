
#include <gdbm.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_database(
	struct database* this)
{
	ENTER;
	
	gdbm_close(this->gdbm);
	
	free(this);
	
	EXIT;
}

