
#include <debug.h>

#include <avl/tree.h>

#include "struct.h"
#include "is_empty.h"

bool recipeset_is_empty(
	struct recipeset* this)
{
	return !this->tree->head;
}

