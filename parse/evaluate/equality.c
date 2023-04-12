
#include <assert.h>
#include <debug.h>

#include <parse/zebu.h>

#include <value/boolean/new.h>
#include <value/compare.h>
#include <value/free.h>

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
		struct value* left = evaluate_equality_expression(expression->left, scope);
		struct value* right = evaluate_relational_expression(expression->right, scope);
		
		result = new_boolean_value(compare_values(left, right) == 0);
		
		free_value(left), free_value(right);
	}
	else if (expression->nq)
	{
		struct value* left = evaluate_equality_expression(expression->left, scope);
		struct value* right = evaluate_relational_expression(expression->right, scope);
		
		result = new_boolean_value(compare_values(left, right) != 0);
		
		free_value(left), free_value(right);
	}
	else
	{
		result = evaluate_relational_expression(expression->inner, scope);
	}
	
	EXIT;
	return result;
}

