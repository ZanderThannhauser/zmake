
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct path* new_root_path()
{
	ENTER;
	
	struct path* this = smalloc(sizeof(*this));
	
	strcpy(this->name, "/");
	
	this->parent = NULL;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

