
#include <debug.h>

#include <value/free.h>
#include <value/boolean/new.h>

#include "assign.h"
#include "assign_builtins.h"

void scope_assign_builtins(
	struct scope* this)
{
	ENTER;
	
	// true:
	{
		struct value* value = new_boolean_value(true);
		
		scope_assign(this, "true", value);
		
		free_value(value);
	}
	
	// false:
	{
		struct value* value = new_boolean_value(false);
		
		scope_assign(this, "false", value);
		
		free_value(value);
	}
	
	EXIT;
}

