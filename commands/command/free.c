
#include <stdlib.h>

#include <debug.h>

#include "simple/free.h"

#include "struct.h"
#include "free.h"

void free_command(
	struct command* this)
{
	ENTER;
	
	for (unsigned i = 0, n = this->simples.n; i < n; i++)
		free_simple_command(this->simples.data[i]);
	
	free(this->simples.data);
	
	free(this->redirect_in);
	
	free(this->redirect_out);
	
	free(this);
	
	EXIT;
}


