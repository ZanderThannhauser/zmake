
#include <stdlib.h>

#include <debug.h>

#include <value/free.h>

#include "struct.h"
#include "free.h"

void free_scope_node(void* ptr)
{
	ENTER;
	
	struct scope_node* node = ptr;
	
	free(node->name);
	
	free_value(node->value);
	
	free(node);
	
	EXIT;
}

