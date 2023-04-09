
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct simple_command* new_simple_command()
{
	ENTER;
	
	struct simple_command* this = smalloc(sizeof(*this));
	
	this->args.data = 0;
	this->args.cap = 0;
	this->args.n = 0;
	
	EXIT;
	return this;
}

