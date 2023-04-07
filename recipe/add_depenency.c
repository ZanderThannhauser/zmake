
#include <debug.h>

#include <recipeset/add.h>

#include "struct.h"
#include "add_depenency.h"

void recipe_add_depenency(
	struct recipe* this,
	struct recipe* depenency)
{
	ENTER;
	
	recipeset_add(this->dep_on, depenency);
	
	recipeset_add(depenency->dep_of, this);
	
	EXIT;
}

