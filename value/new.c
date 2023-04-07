
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct value* new_value(
	enum value_kind kind,
	struct value_inheritance* inheritance,
	size_t alloc_size)
{
	ENTER;
	
	struct value* this = smalloc(alloc_size);
	
	this->kind = kind;
	this->inheritance = inheritance;
	this->refcount = 1;
	
	EXIT;
	return this;
}

