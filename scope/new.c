
#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>

#include "node/compare.h"
#include "node/free.h"

#include "struct.h"
#include "new.h"

struct scope* new_scope()
{
	ENTER;
	
	struct scope* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_scope_nodes, free_scope_node);
	
	EXIT;
	return this;
}

