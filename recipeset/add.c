
#include <assert.h>

#include <debug.h>

#include <avl/insert.h>

#include <recipe/inc.h>

#include "struct.h"
#include "add.h"

bool recipeset_add(
	struct recipeset* this,
	struct recipe* recipe)
{
	bool new;
	ENTER;
	
	struct avl_node_t* node = avl_insert(this->tree, recipe);
	
	if (node)
	{
		new = true;
		if (this->should_refcount_elements) inc_recipe(recipe);
		this->n++;
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return new;
}

