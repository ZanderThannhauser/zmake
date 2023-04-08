
#include <assert.h>

#include <debug.h>

#include <parse/zebu.h>

#include <value/boolean/new.h>
#include <value/compare.h>
#include <value/free.h>

#include "shift.h"
#include "relational.h"

struct value* evaluate_relational_expression(
	struct zebu_relational_expression* expression,
	struct scope* scope)
{
	struct value* result;
	ENTER;
	
	if (expression->inner)
	{
		result = evaluate_shift_expression(expression->inner, scope);
	}
	else if (expression->gt)
	{
		struct value* left  = evaluate_relational_expression(expression->left, scope);
		struct value* right = evaluate_shift_expression(expression->right, scope);
		
		result = new_boolean_value(compare_values(left, right) > 0);
		
		free_value(left), free_value(right);
	}
	else if (expression->gte)
	{
		struct value* left  = evaluate_relational_expression(expression->left, scope);
		struct value* right = evaluate_shift_expression(expression->right, scope);
		
		result = new_boolean_value(compare_values(left, right) >= 0);
		
		free_value(left), free_value(right);
	}
	else if (expression->lt)
	{
		struct value* left  = evaluate_relational_expression(expression->left, scope);
		struct value* right = evaluate_shift_expression(expression->right, scope);
		
		result = new_boolean_value(compare_values(left, right) < 0);
		
		free_value(left), free_value(right);
	}
	else if (expression->lte)
	{
		struct value* left  = evaluate_relational_expression(expression->left, scope);
		struct value* right = evaluate_shift_expression(expression->right, scope);
		
		result = new_boolean_value(compare_values(left, right) <= 0);
		
		free_value(left), free_value(right);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return result;
}








