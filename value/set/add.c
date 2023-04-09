
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include "../inc.h"

#include "struct.h"
#include "add.h"

void set_value_add(
	struct set_value* this,
	struct value* element)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, element);
	
	if (!node)
	{
		avl_insert(this->tree, inc_value(element));
		
		this->len++;
	}
	
	EXIT;
}

