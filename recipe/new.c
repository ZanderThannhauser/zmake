
#include <string.h>
#include <debug.h>

#include <memory/smalloc.h>

#include <parse/zebu.h>

#include <recipeset/new.h>

#include <dirfd/inc.h>

#include "struct.h"
#include "new.h"

struct recipe* new_recipe(
	const char* target,
	struct dirfd* dirfd)
{
	ENTER;
	
	struct recipe* this = smalloc(sizeof(*this));
	
	this->target = strdup(target);
	this->dirfd = inc_dirfd(dirfd);
	
	this-> dep_on = new_recipeset(false);
	this->odep_on = new_recipeset(false);
	this-> dep_of = new_recipeset(false);
	
	this->circular.checked = 0;
	this->circular.visited = false;
	
	this->execution.round = 0;
	this->execution.marked = false;
	
	this->commands = NULL;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

