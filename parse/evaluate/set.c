
#include <assert.h>

#include <debug.h>

#include <memory/srealloc.h>

#include <parse/zebu.h>

#include <value/inc.h>
#include <value/free.h>
#include <value/set/new.h>

#include "root.h"
#include "set.h"

struct value* evaluate_set_expression(
	struct zebu_primary_expression* expression,
	struct scope* scope)
{
	ENTER;
	
	struct value* result = new_set_value();
	
	for (unsigned i = 0, n = expression->elements.n; i < n; i++)
	{
		TODO;
		#if 0
		struct zebu_expression* zelement = expression->elements.data[i];
		
		struct value* element = evaluate_expression(zelement, scope);
		
		if (elements.n == elements.cap)
		{
			elements.cap = elements.cap << 1 ?: 1;
			elements.data = srealloc(elements.data, sizeof(*elements.data) * elements.cap);
		}
		
		elements.data[elements.n++] = inc_value(element);
		
		free_value(element);
		#endif
	}
	
	EXIT;
	return result;
}













