
#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_recipeset(
	struct recipeset* this)
{
	ENTER;
	
	if (this)
	{
		avl_free_tree(this->tree);
		free(this);
	}
	
	EXIT;
}

