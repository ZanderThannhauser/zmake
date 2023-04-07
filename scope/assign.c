
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <value/inc.h>
#include <value/free.h>

#include "node/struct.h"
#include "node/new.h"

#include "struct.h"
#include "assign.h"

void scope_assign(
	struct scope* this,
	const char* name,
	struct value* value)
{
	ENTER;
	
	dpvs(name);
	
	struct avl_node_t* node = avl_search(this->tree, &name);
	
	if (node)
	{
		struct scope_node* item = node->item;
		
		free_value(item->value);
		
		item->value = inc_value(value);
	}
	else
	{
		struct scope_node* item = new_scope_node(name, value);
		
		avl_insert(this->tree, item);
	}
	
	EXIT;
}

