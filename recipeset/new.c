
#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>

#include <recipe/compare_targets.h>
#include <recipe/free.h>

#include "struct.h"
#include "new.h"

struct recipeset* new_recipeset(
	bool should_refcount_elements)
{
	ENTER;
	
	struct recipeset* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_recipe_targets,
		should_refcount_elements ? free_recipe : NULL);
	this->should_refcount_elements = should_refcount_elements;
	this->n = 0;
	
	EXIT;
	return this;
}

