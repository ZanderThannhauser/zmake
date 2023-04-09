
#include <stdlib.h>

#include <debug.h>

#include "command/free.h"

#include "struct.h"
#include "free.h"

void free_commands(
	struct commands* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		for (unsigned i = 0, n = this->n; i < n; i++)
			free_command(this->data[i]);
		
		free(this->data);
		free(this);
	}
	
	EXIT;
}


