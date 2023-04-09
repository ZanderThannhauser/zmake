
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_set_value(
	struct value* super)
{
	ENTER;
	
	struct set_value* this = (void*) super;
	
	avl_free_tree(this->tree);
	
	EXIT;
}

