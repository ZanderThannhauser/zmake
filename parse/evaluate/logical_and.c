
#include <assert.h>

#include <debug.h>

#include <parse/zebu.h>

#include "inclusive_or.h"
#include "logical_and.h"

struct value* evaluate_logical_and_expression(
	struct zebu_logical_and_expression* expression,
	struct scope* scope)
{
	struct value* result;
	ENTER;
	
	if (expression->inner)
	{
		result = evaluate_inclusive_or_expression(expression->inner, scope);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return result;
}

