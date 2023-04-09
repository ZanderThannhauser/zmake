
#include <debug.h>

#include <avl/tree.h>

#include "struct.h"
#include "foreach.h"

void set_value_foreach(
	struct set_value* this,
	void (*callback)(struct value*))
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
		callback(node->item);
	
	EXIT;
}

