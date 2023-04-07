
#include <string.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <value/inc.h>

#include "struct.h"
#include "new.h"

struct scope_node* new_scope_node(
	const char* name,
	struct value* value)
{
	ENTER;
	
	struct scope_node* this = smalloc(sizeof(*this));
	
	this->name = strdup(name);
	
	this->value = inc_value(value);
	
	EXIT;
	return this;
}

