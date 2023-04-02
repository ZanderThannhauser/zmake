
#include <debug.h>

#include <avl/search.h>

#include "struct.h"
#include "lookup.h"

struct recipe* recipeset_lookup(
	const struct recipeset* this,
	const char* target)
{
	struct avl_node_t* node = avl_search(this->tree, &target);
	
	return node ? node->item : NULL;
}

