
#include <assert.h>
#include <debug.h>

#include <parse/zebu.h>

#include "relational.h"
#include "equality.h"

struct value* evaluate_equality_expression(
	struct zebu_equality_expression* expression,
	struct scope* scope)
{
	struct value* result;
	ENTER;
	
	if (expression->eq)
	{
		TODO;
	}
	else if (expression->nq)
	{
		TODO;
	}
	else
	{
		result = evaluate_relational_expression(expression->inner, scope);
	}
	
	EXIT;
	return result;
}

