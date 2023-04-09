
#include <stdlib.h>

#include <debug.h>

#include <recipeset/free.h>

#include <parse/zebu.h>

#include <dirfd/free.h>

#include <commands/free.h>

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
		
		free_recipeset(this->odep_on);
		
		free_recipeset(this->dep_of);
		
		free_commands(this->commands);
		
		free(this);
	}
	
	EXIT;
}











