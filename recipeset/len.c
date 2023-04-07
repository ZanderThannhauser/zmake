
#include <debug.h>

#include <avl/tree.h>

#include "struct.h"
#include "len.h"

unsigned recipeset_len(
	struct recipeset* this)
{
	return this->n;
}

