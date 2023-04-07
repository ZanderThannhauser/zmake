
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "free.h"

void free_value(
	struct value* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		(this->inheritance->free)(this);
		free(this);
	}
	
	EXIT;
}

