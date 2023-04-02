
#include <debug.h>

#include <avl/tree.h>

#include "struct.h"
#include "foreach.h"

void recipeset_foreach(
	const struct recipeset* this,
	void (*callback)(struct recipe* recipe))
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
		callback(node->item);
	
	EXIT;
}

