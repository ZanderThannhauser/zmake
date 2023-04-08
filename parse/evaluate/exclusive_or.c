
#include <assert.h>

#include <debug.h>

#include <parse/zebu.h>

#include "and.h"
#include "exclusive_or.h"

struct value* evaluate_exclusive_or_expression(
	struct zebu_exclusive_or_expression* expression,
	struct scope* scope)
{
	struct value* result;
	ENTER;
	
	if (expression->inner)
	{
		result = evaluate_and_expression(expression->inner, scope);
	}
	else
	{
		TODO;
	}
	
	
	EXIT;
	return result;
}

