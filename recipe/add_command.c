
#include <debug.h>

#include <memory/srealloc.h>

#include "struct.h"
#include "add_command.h"

void recipe_add_command(
	struct recipe* recipe,
	struct command* command)
{
	ENTER;
	
	if (recipe->commands.n == recipe->commands.cap)
	{
		recipe->commands.cap = recipe->commands.cap << 1 ?: 1;
		recipe->commands.data = srealloc(recipe->commands.data,
			sizeof(*recipe->commands.data) * recipe->commands.cap);
	}
	
	recipe->commands.data[recipe->commands.n++] = command;
	
	EXIT;
}

