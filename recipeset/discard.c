
#include <debug.h>

#include <avl/delete.h>

#include "struct.h"
#include "discard.h"

bool recipeset_discard(
	struct recipeset* this,
	struct recipe* recipe)
{
	if (avl_delete(this->tree, recipe))
		this->n--;
	return !!this->n;
}

