
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <value/print.h>
#include <value/free.h>

#include "evaluate/root.h"

#include "zebu.h"
#include "print.h"

void evaluate_print_statement(
	struct zebu_print* print,
	struct scope* scope)
{
	ENTER;
	
	struct value* result = evaluate_expression(print->expression, scope);
	
	value_print(result), puts("");
	
	free_value(result);
	
	if (print->print)
		;
	else if (print->error)
		exit(1);
	else
	{
		TODO;
	}
	
	EXIT;
}

