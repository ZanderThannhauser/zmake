
#include <debug.h>

#include <memory/srealloc.h>

#include <parse/zebu.h>

#include <value/inc.h>
#include <value/free.h>
#include <value/list/new.h>

#include "root.h"
#include "list.h"

struct value* evaluate_list_expression(
	struct zebu_primary_expression* expression,
	struct scope* scope)
{
	ENTER;
	
	struct {
		struct value** data;
		unsigned n, cap;
	} elements = {};
	
	for (unsigned i = 0, n = expression->elements.n; i < n; i++)
	{
		struct zebu_expression* zelement = expression->elements.data[i];
		
		struct value* element = evaluate_expression(zelement, scope);
		
		if (elements.n == elements.cap)
		{
			elements.cap = elements.cap << 1 ?: 1;
			elements.data = srealloc(elements.data, sizeof(*elements.data) * elements.cap);
		}
		
		elements.data[elements.n++] = inc_value(element);
		
		free_value(element);
	}
	
	struct value* result = new_list_value(elements.data, elements.n);
	
	EXIT;
	return result;
}













