
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <debug.h>

#include <parse/zebu.h>

#include <value/free.h>
#include <value/string/struct.h>
#include <value/list/struct.h>
#include <value/struct.h>

#include "root.h"
#include "string.h"
#include "argument.h"

static void helper(
	struct value* value,
	void (*callback)(char*))
{
	if (value->kind == vk_string)
	{
		struct string_value* spef = (void*) value;
		
		callback(strdup(spef->chars));
	}
	else if (value->kind == vk_list)
	{
		struct list_value* spef = (void*) value;
		
		for (unsigned i = 0, n = spef->len; i < n; i++)
			helper(spef->elements[i], callback);
	}
	else
	{
		TODO;
		exit(1);
	}
}

void evaluate_argument(
	struct zebu_argument* argument,
	struct scope* scope,
	void (*callback)(char*))
{
	ENTER;
	
	if (argument->expression)
	{
		struct value* result = evaluate_expression(argument->expression, scope);
		
		helper(result, callback);
		
		free_value(result);
	}
	else if (argument->text)
	{
		callback(strdup((char*) argument->text->data));
	}
	else if (argument->string)
	{
		callback(escape_zebu_string(argument->string));
	}
	else
	{
		TODO;
	}
	
	EXIT;
}











