
#include <debug.h>

#include <avl/free_nodes.h>

#include "struct.h"
#include "clear.h"

void recipeset_clear(
	struct recipeset* this)
{
	ENTER;
	
	avl_free_nodes(this->tree);
	
	this->n = 0;
	
	EXIT;
}

