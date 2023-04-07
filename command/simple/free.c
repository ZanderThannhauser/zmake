
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_simple_command(
	struct simple_command* this)
{
	ENTER;
	
	for (unsigned i = 0, n = this->args.n; i < n; i++)
		free(this->args.data[i]);
	
	free(this->args.data);
	
	free(this);
	
	EXIT;
}

