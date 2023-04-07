
#include <assert.h>

#include <debug.h>

#include <parse/zebu.h>

#include "postfix.h"
#include "prefix.h"

struct value* evaluate_prefix_expression(
	struct zebu_prefix_expression* expression,
	struct scope* scope)
{
	struct value* result;
	ENTER;
	
	if (expression->pos)
	{
		TODO;
	}
	else if (expression->neg)
	{
		TODO;
	}
	else
	{
		result = evaluate_postfix_expression(expression->inner, scope);
	}
	
	EXIT;
	return result;
}

