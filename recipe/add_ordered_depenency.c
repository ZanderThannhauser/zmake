
#include <debug.h>

#include <recipeset/add.h>

#include "struct.h"
#include "add_ordered_depenency.h"

void recipe_add_ordered_depenency(
	struct recipe* this,
	struct recipe* depenency)
{
	ENTER;
	
	recipeset_add(this->odep_on, depenency);
	
	recipeset_add(depenency->dep_of, this);
	
	EXIT;
}

