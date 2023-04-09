
#include <debug.h>

#include <memory/srealloc.h>

#include "struct.h"
#include "append.h"

void simple_command_append(
	struct simple_command* this,
	char* arg)
{
	ENTER;
	
	dpvs(arg);
	
	while (this->args.n + 1 >= this->args.cap)
	{
		this->args.cap = this->args.cap << 1 ?: 1;
		this->args.data = srealloc(this->args.data,
			sizeof(*this->args.data) * this->args.cap);
	}
	
	this->args.data[this->args.n++] = arg;
	
	this->args.data[this->args.n] = NULL;
	
	EXIT;
}

