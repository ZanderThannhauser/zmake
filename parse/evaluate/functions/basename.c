
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <value/struct.h>
#include <value/string/struct.h>
#include <value/string/new.h>
#include <value/inc.h>
#include <value/free.h>

#include <parse/zebu.h>

#include "../root.h"

#include "basename.h"

struct value* evaluate_basename_function(
	struct zebu_primary_expression* expression,
	struct scope* scope)
{
	struct value* result;
	ENTER;
	
	struct value* gpath = evaluate_expression(expression->path, scope);
	
	if (gpath->kind != vk_string)
	{
		TODO;
		exit(1);
	}
	
	struct string_value* path = (void*) gpath;
	
	dpvs(path->chars);
	
	char* slash = rindex(path->chars, '/');
	char* dot = rindex(path->chars, '.');
	
	if (dot && (!slash || slash < dot))
		result = new_string_value(path->chars, dot - path->chars);
	else
		result = inc_value(gpath);
	
	free_value(gpath);
	
	EXIT;
	return result;
}














