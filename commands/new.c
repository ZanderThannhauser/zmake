
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct commands* new_commands()
{
	ENTER;
	
	struct commands* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->n = 0;
	this->cap = 0;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

