
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include <parse/zebu.h>

#include <scope/lookup.h>

#include <defines/argv0.h>

#include "functions/basename.h"
#include "functions/dir.h"
#include "set.h"
#include "list.h"
#include "root.h"
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
		result = evaluate_expression(expression->inner, scope);
	}
	else if (expression->variable)
	{
		const char* name = (char*) expression->variable->data;
		
		result = scope_lookup(scope, name);
		
		if (!result)
		{
			fprintf(stderr, "%s: use of undefined variable "
				"'%s' on line %u!\n", argv0, name, expression->startline);
			exit(e_undefined_variable);
		}
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
	else if (expression->set)
	{
		result = evaluate_set_expression(expression, scope);
	}
	else if (expression->basename)
	{
		result = evaluate_basename_function(expression, scope);
	}
	else if (expression->dir)
	{
		result = evaluate_dir_function(expression, scope);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return result;
}













