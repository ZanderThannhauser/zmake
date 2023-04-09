
#include <debug.h>

#include <memory/srealloc.h>

#include "struct.h"
#include "append.h"

void command_append(
	struct command* this,
	struct simple_command* simple)
{
	ENTER;
	
	if (this->simples.n == this->simples.cap)
	{
		this->simples.cap = this->simples.cap << 1 ?: 1;
		this->simples.data = srealloc(this->simples.data,
			sizeof(*this->simples.data) * this->simples.cap);
	}
	
	this->simples.data[this->simples.n++] = simple;
	
	EXIT;
}

