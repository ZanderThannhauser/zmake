
#include <stddef.h>

#include <debug.h>

#include <avl/search.h>

#include <recipe/struct.h>

#include "struct.h"
#include "lookup.h"

struct recipe* recipeset_lookup(
	const struct recipeset* this,
	const char* target,
	struct dirfd* dirfd)
{
	struct avl_node_t* node = avl_search(this->tree,
		&(struct {
			const char* target;
			struct dirfd* dirfd;
		}) {target, dirfd});
	
	return node ? node->item : NULL;
}

