
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct command* new_command()
{
	ENTER;
	
	struct command* this = smalloc(sizeof(*this));
	
	this->simples.data = NULL;
	this->simples.cap = 0;
	this->simples.n = 0;
	
	this->redirect_in = NULL;
	this->redirect_out = NULL;
	
	EXIT;
	return this;
}

