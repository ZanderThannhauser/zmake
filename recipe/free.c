
#include <stdlib.h>

#include <debug.h>

#include <recipeset/free.h>

#include <parse/zebu.h>

#include <dirfd/free.h>

#include <command/free.h>

#include "struct.h"
#include "free.h"

void free_recipe(
	void* ptr)
{
	ENTER;
	
	struct recipe* this = ptr;
	
	if (this && !--this->refcount)
	{
		free(this->target);
		
		free_dirfd(this->dirfd);
		
		free_recipeset(this->dep_on);
		
		free_recipeset(this->dep_of);
		
		for (unsigned i = 0, n = this->commands.n; i < n; i++)
			free_command(this->commands.data[i]);
		
		free(this->commands.data);
		
		free(this);
	}
	
	EXIT;
}











