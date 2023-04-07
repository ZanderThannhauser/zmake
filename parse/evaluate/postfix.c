
#include <debug.h>

#include <parse/zebu.h>

#include "primary.h"
#include "postfix.h"

struct value* evaluate_postfix_expression(
	struct zebu_postfix_expression* expression,
	struct scope* scope)
{
	ENTER;
	
	struct value* result = evaluate_primary_expression(expression->inner, scope);
	
	EXIT;
	return result;
}

