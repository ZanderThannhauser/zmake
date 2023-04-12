
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include <defines/argv0.h>

#include <avl/search.h>

#include <value/inc.h>

#include "node/struct.h"

#include "struct.h"
#include "lookup.h"

struct value* scope_lookup(
	struct scope* this,
	const char* name)
{
	struct value* retval = NULL;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &name);
	
	if (node)
	{
		struct scope_node* snode = node->item;
		
		retval = inc_value(snode->value);
	}
	
	EXIT;
	return retval;
}

