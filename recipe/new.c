
#include <debug.h>

#include <memory/smalloc.h>

#include <parse/zebu.h>

#include <recipeset/new.h>

#include "struct.h"
#include "new.h"

struct recipe* new_recipe(
	char* target,
	struct zebu_commands* commands)
{
	ENTER;
	
	struct recipe* this = smalloc(sizeof(*this));
	
	this->target = target;
	
	this->commands = inc_zebu_commands(commands);
	
	this->dep_on = new_recipeset(true);
	this->dep_of = new_recipeset(false);
	
	this->circular.checked = false;
	this->circular.visited = false;
	
	this->scores.total = 0;
	this->scores.count = 0;
	this->scores.real = -1;
	this->scores.effective = -1;
	
	this->execution.marked = false;
	this->execution.waiting = 0;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

