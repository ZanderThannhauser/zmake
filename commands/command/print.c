
#include <assert.h>
#include <stdio.h>

#include <debug.h>

#include "simple/print.h"

#include "struct.h"
#include "print.h"

void command_print(
	struct command* this)
{
	ENTER;
	
	dpv(this->simples.n);
	
	printf("\e[33m$ ");
	
	assert(this->simples.n);
	
	simple_command_print(this->simples.data[0]);
	
	if (this->redirect_in)
		printf(" < %s", this->redirect_in);
	
	for (unsigned i = 1, n = this->simples.n; i < n; i++)
		printf(" | "), simple_command_print(this->simples.data[i]);
	
	if (this->redirect_out)
		printf(" > %s", this->redirect_out);
	
	printf("\e[0m\n");
	
	EXIT;
}

