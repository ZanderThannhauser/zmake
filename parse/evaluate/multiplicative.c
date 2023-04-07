
#include <stdlib.h>
#include <assert.h>
#include <gmp.h>

#include <debug.h>

#include <enums/error.h>

#include <parse/zebu.h>

#include <value/integer/struct.h>
#include <value/integer/new.h>
#include <value/struct.h>
#include <value/free.h>

#include "prefix.h"
#include "multiplicative.h"

struct value* evaluate_multiplicative_expression(
	struct zebu_multiplicative_expression* expression,
	struct scope* scope)
{
	struct value* result;
	ENTER;
	
	if (expression->mul)
	{
		struct value* left = evaluate_multiplicative_expression(expression->left, scope);
		
		struct value* right = evaluate_prefix_expression(expression->right, scope);
		
		if (left->kind == vk_integer && right->kind == vk_integer)
		{
			struct integer_value* spef_left = (void*) left;
			struct integer_value* spef_right = (void*) right;
			
			mpz_t product;
			
			mpz_init(product);
			
			mpz_mul(product, spef_left->value, spef_right->value);
			
			result = new_integer_value(product);
			
			mpz_clear(product);
		}
		else
		{
			TODO;
			exit(e_type_check_error);
		}
		
		free_value(left), free_value(right);
	}
	else if (expression->div)
	{
		struct value* left = evaluate_multiplicative_expression(expression->left, scope);
		
		struct value* right = evaluate_prefix_expression(expression->right, scope);
		
		if (left->kind == vk_integer && right->kind == vk_integer)
		{
			struct integer_value* spef_left = (void*) left;
			struct integer_value* spef_right = (void*) right;
			
			mpz_t quoicent;
			
			mpz_init(quoicent);
			
			mpz_fdiv_q(quoicent, spef_left->value, spef_right->value);
			
			result = new_integer_value(quoicent);
			
			mpz_clear(quoicent);
		}
		else
		{
			TODO;
			exit(e_type_check_error);
		}
		
		free_value(left), free_value(right);
	}
	else
	{
		result = evaluate_prefix_expression(expression->inner, scope);
	}
	
	EXIT;
	return result;
}

