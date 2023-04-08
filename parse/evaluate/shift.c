
#include <assert.h>

#include <debug.h>

#include <parse/zebu.h>

#include "additive.h"
#include "shift.h"

struct value* evaluate_shift_expression(
	struct zebu_shift_expression* expression,
	struct scope* scope)
{
	struct value* result;
	ENTER;
	
	if (expression->inner)
	{
		result = evaluate_additive_expression(expression->inner, scope);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return result;
}

