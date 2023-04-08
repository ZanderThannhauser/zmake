
#include <assert.h>

#include <debug.h>

#include <parse/zebu.h>

#include "exclusive_or.h"
#include "inclusive_or.h"

struct value* evaluate_inclusive_or_expression(
	struct zebu_inclusive_or_expression* expression,
	struct scope* scope)
{
	struct value* result;
	ENTER;
	
	if (expression->inner)
	{
		result = evaluate_exclusive_or_expression(expression->inner, scope);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return result;
}

