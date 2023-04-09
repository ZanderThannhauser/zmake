
#include <debug.h>

#include <memory/srealloc.h>

#include <parse/zebu.h>

#include <value/free.h>
#include <value/list/new.h>
#include <value/list/append.h>

#include "root.h"
#include "list.h"

struct value* evaluate_list_expression(
	struct zebu_primary_expression* expression,
	struct scope* scope)
{
	ENTER;
	
	struct list_value* result = (void*) new_list_value();
	
	for (unsigned i = 0, n = expression->elements.n; i < n; i++)
	{
		struct zebu_expression* zelement = expression->elements.data[i];
		
		struct value* element = evaluate_expression(zelement, scope);
		
		list_value_append(result, element);
		
		free_value(element);
	}
	
	EXIT;
	return (void*) result;
}













