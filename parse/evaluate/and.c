
#include <assert.h>

#include <debug.h>

#include <parse/zebu.h>

#include "equality.h"
#include "and.h"

struct value* evaluate_and_expression(
	struct zebu_and_expression* expression,
	struct scope* scope)
{
	struct value* result;
	ENTER;
	
	if (expression->inner)
	{
		result = evaluate_equality_expression(expression->inner, scope);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return result;
}

