
#include <assert.h>

#include <debug.h>

#include <parse/zebu.h>

#include "additive.h"
#include "relational.h"

struct value* evaluate_relational_expression(
	struct zebu_relational_expression* expression,
	struct scope* scope)
{
	struct value* result;
	ENTER;
	
	if (expression->gt)
	{
		TODO;
	}
	else if (expression->gte)
	{
		TODO;
	}
	else if (expression->lt)
	{
		TODO;
	}
	else if (expression->lte)
	{
		TODO;
	}
	else
	{
		result = evaluate_additive_expression(expression->inner, scope);
	}
	
	EXIT;
	return result;
}

