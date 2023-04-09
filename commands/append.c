
#include <debug.h>

#include <memory/srealloc.h>

#include "struct.h"
#include "append.h"

void commands_append(
	struct commands* this,
	struct command* command)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = command;
	
	EXIT;
}


