
#include <debug.h>

#include <avl/tree.h>

#include "struct.h"
#include "any.h"

bool recipeset_any(
	const struct recipeset* this,
	bool (*callback)(const struct recipe*))
{
	ENTER;
	
	bool any = false;
	
	for (struct avl_node_t* node = this->tree->head; !any && node; node = node->next)
		any = callback(node->item);
	
	EXIT;
	return any;
}

