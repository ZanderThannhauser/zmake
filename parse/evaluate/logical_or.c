
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <parse/zebu.h>

#include <value/struct.h>
#include <value/boolean/struct.h>
#include <value/free.h>

#include "logical_and.h"
#include "logical_or.h"

struct value* perform_logical_or(
	struct value* left,
	struct value* right)
{
	TODO;
}

struct value* evaluate_logical_or_expression(
	struct zebu_logical_or_expression* expression,
	struct scope* scope)
{
	struct value* result;
	ENTER;
	
	if (expression->inner)
	{
		result = evaluate_logical_and_expression(expression->inner, scope);
	}
	else
	{
		struct value* left  = evaluate_logical_or_expression(expression->left, scope);
		
		if (left->kind != vk_boolean)
		{
			TODO;
			exit(1);
		}
		
		if (((struct boolean_value*) left)->value)
			result = left;
		else
			result = evaluate_logical_and_expression(expression->right, scope);
	}
	
	EXIT;
	return result;
}














