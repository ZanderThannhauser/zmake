
#include <gmp.h>

#include <debug.h>

#include "struct.h"
#include "print.h"

void integer_value_print(
	struct value* super)
{
	ENTER;
	
	struct integer_value* this = (void*) super;
	
	gmp_printf("%Zi", this->value);
	
	EXIT;
}

