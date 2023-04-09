
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <debug.h>

#include <enums/error.h>

#include <memory/smalloc.h>

#include <parse/zebu.h>

#include <value/integer/struct.h>
#include <value/integer/new.h>
#include <value/string/struct.h>
#include <value/string/new.h>
#include <value/list/struct.h>
#include <value/list/new.h>
#include <value/list/append.h>
#include <value/set/add.h>
#include <value/struct.h>
#include <value/inc.h>
#include <value/free.h>

#include "multiplicative.h"
#include "additive.h"

struct value* perform_add(
	struct value* left,
	struct value* right)
{
	struct value* result;
	ENTER;
	
	if (left->kind == vk_integer && right->kind == vk_integer)
	{
		struct integer_value* spef_left = (void*) left;
		struct integer_value* spef_right = (void*) right;
		
		mpz_t sum;
		
		mpz_init(sum);
		
		mpz_add(sum, spef_left->value, spef_right->value);
		
		result = new_integer_value(sum);
		
		mpz_clear(sum);
	}
	else if (left->kind == vk_string && right->kind == vk_string)
	{
		struct string_value* spef_left = (void*) left;
		struct string_value* spef_right = (void*) right;
		
		unsigned len = spef_left->len + spef_right->len;
		
		char* chars = smalloc(len + 1);
		
		stpcpy(stpcpy(chars, spef_left->chars), spef_right->chars);
		
		dpvs(chars);
		
		result = new_string_value(chars, len);
		
		free(chars);
	}
	else if (left->kind == vk_list && right->kind == vk_list)
	{
		TODO;
		#if 0
		struct list_value* spef_left = (void*) left;
		struct list_value* spef_right = (void*) right;
		
		unsigned len = spef_left->len + spef_right->len;
		
		struct value** elements = smalloc(sizeof(*elements) * len);
		
		unsigned i = 0, n = spef_left->len;
		for (; i < n; i++)
			elements[i] = inc_value(spef_left->elements[i]);
		
		for (unsigned j = 0, m = spef_right->len; j < m; j++)
			elements[i + j] = inc_value(spef_right->elements[j]);
		
		result = new_list_value(elements, len);
		#endif
	}
	else if (left->kind == vk_set && right->kind == vk_set)
	{
		TODO;
	}
	else
	{
		TODO;
		exit(e_type_check_error);
	}
	
	EXIT;
	return result;
}

void perform_addeq(
	struct value* left,
	struct value* right)
{
	ENTER;
	
	if (left->kind == vk_integer && right->kind == vk_integer)
	{
		TODO;
	}
	else if (left->kind == vk_string && right->kind == vk_string)
	{
		TODO;
	}
	else if (left->kind == vk_list && right->kind == vk_list)
	{
		struct list_value* spef_left = (void*) left;
		struct list_value* spef_right = (void*) right;
		
		for (unsigned i = 0, n = spef_right->len; i < n; i++)
			list_value_append(spef_left, spef_right->elements[i]);
	}
	else if (left->kind == vk_list)
	{
		struct list_value* spef_left = (void*) left;
		
		list_value_append(spef_left, right);
	}
	else if (left->kind == vk_set && right->kind == vk_set)
	{
		TODO;
	}
	else if (left->kind == vk_set)
	{
		struct set_value* spef_left = (void*) left;
		
		set_value_add(spef_left, right);
	}
	else
	{
		TODO;
		exit(1);
	}
	
	EXIT;
}

struct value* perform_sub(
	struct value* left,
	struct value* right)
{
	struct value* result;
	ENTER;
	
	if (left->kind == vk_integer && right->kind == vk_integer)
	{
		struct integer_value* spef_left = (void*) left;
		struct integer_value* spef_right = (void*) right;
		
		mpz_t diff;
		
		mpz_init(diff);
		
		mpz_sub(diff, spef_left->value, spef_right->value);
		
		result = new_integer_value(diff);
		
		mpz_clear(diff);
	}
	else if (left->kind == vk_string && right->kind == vk_string)
	{
		struct string_value* spef_left = (void*) left;
		struct string_value* spef_right = (void*) right;
		
		unsigned len;
		const char* chars;
		if (true
			&& spef_left->len == spef_right->len
			&& !memcmp(spef_left->chars, spef_right->chars, spef_left->len))
		{
			len = 0, chars = "";
		}
		else if (true
			&& spef_left->len < spef_right->len
			&& !memcmp(spef_left->chars, spef_right->chars, spef_left->len))
		{
			len = spef_right->len - spef_left->len;
			chars = spef_right->chars + spef_left->len;
		}
		else if (true
			&& spef_left->len > spef_right->len
			&& !memcmp(
				spef_left->chars + spef_left->len - spef_right->len,
				spef_right->chars,
				spef_right->len))
		{
			len = spef_left->len - spef_right->len;
			chars = spef_left->chars;
		}
		else
		{
			TODO;
		}
		
		result = new_string_value(chars, len);
	}
	else
	{
		TODO;
		exit(e_type_check_error);
	}
	
	EXIT;
	return result;
}

struct value* evaluate_additive_expression(
	struct zebu_additive_expression* expression,
	struct scope* scope)
{
	struct value* result;
	ENTER;
	
	if (expression->add)
	{
		struct value* left = evaluate_additive_expression(expression->left, scope);
		
		struct value* right = evaluate_multiplicative_expression(expression->right, scope);
		
		result = perform_add(left, right);
		
		free_value(left), free_value(right);
	}
	else if (expression->sub)
	{
		struct value* left = evaluate_additive_expression(expression->left, scope);
		
		struct value* right = evaluate_multiplicative_expression(expression->right, scope);
		
		result = perform_sub(left, right);
		
		free_value(left), free_value(right);
	}
	else
	{
		result = evaluate_multiplicative_expression(expression->inner, scope);
	}
	
	EXIT;
	return result;
}














