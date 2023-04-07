
#include <assert.h>

#include <debug.h>

#include <parse/zebu.h>

#include <scope/lookup.h>

#include "list.h"
#include "integer.h"
#include "string.h"
#include "primary.h"

struct value* evaluate_primary_expression(
	struct zebu_primary_expression* expression,
	struct scope* scope)
{
	struct value* result;
	ENTER;
	
	if (expression->inner)
	{
		TODO;
	}
	else if (expression->variable)
	{
		const char* name = (char*) expression->variable->data;
		
		dpvs(name);
		
		result = scope_lookup(scope, name);
	}
	else if (expression->integer)
	{
		result = evaluate_integer_expression(expression->integer);
	}
	else if (expression->string)
	{
		result = evaluate_string_expression(expression->string);
	}
	else if (expression->list)
	{
		result = evaluate_list_expression(expression, scope);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return result;
}













