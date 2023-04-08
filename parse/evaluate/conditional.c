
#include <assert.h>

#include <debug.h>

#include <parse/zebu.h>

#include "logical_or.h"
#include "conditional.h"

struct value* evaluate_conditional_expression(
	struct zebu_conditional_expression* expression,
	struct scope* scope)
{
	struct value* result;
	ENTER;
	
	if (expression->truecase)
	{
		TODO;
	}
	else
	{
		result = evaluate_logical_or_expression(expression->inner, scope);
	}
	
	EXIT;
	return result;
}

