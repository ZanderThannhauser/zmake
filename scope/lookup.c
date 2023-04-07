
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include <avl/search.h>

#include <value/inc.h>

#include "node/struct.h"

#include "struct.h"
#include "lookup.h"

struct value* scope_lookup(
	struct scope* this,
	const char* name)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &name);
	
	if (!node)
	{
		TODO;
		exit(e_undefined_variable);
	}
	
	struct scope_node* snode = node->item;
	
	struct value* retval = inc_value(snode->value);
	
	EXIT;
	return retval;
}

