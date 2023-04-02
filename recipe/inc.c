
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct recipe* inc_recipe(
	struct recipe* this)
{
	if (this)
		this->refcount++;
	return this;
}

