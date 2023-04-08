
#include <debug.h>

#include <parse/zebu.h>

#include "conditional.h"
#include "root.h"

struct value* evaluate_expression(
	struct zebu_expression* expression,
	struct scope* scope)
{
	ENTER;
	
	struct value* result = evaluate_conditional_expression(expression->inner, scope);
	
	EXIT;
	return result;
}

