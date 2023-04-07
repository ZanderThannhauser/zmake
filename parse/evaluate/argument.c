
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <debug.h>

#include <parse/zebu.h>

#include <value/free.h>
#include <value/string/struct.h>
#include <value/struct.h>

#include "root.h"
#include "string.h"
#include "argument.h"

char* evaluate_argument(
	struct zebu_argument* argument,
	struct scope* scope)
{
	char* retval;
	ENTER;
	
	if (argument->expression)
	{
		struct value* result = evaluate_expression(argument->expression, scope);
		
		if (result->kind != vk_string)
		{
			TODO;
			exit(1);
		}
		
		struct string_value* spef = (void*) result;
		
		retval = strdup(spef->chars);
		
		free_value(result);
	}
	else if (argument->text)
	{
		retval = strdup((char*) argument->text->data);
	}
	else if (argument->string)
	{
		retval = escape_zebu_string(argument->string);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}

