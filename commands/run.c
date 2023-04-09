
#include <debug.h>

#include <cmdln/options/dry_run.h>

#include "command/print.h"
#include "command/run.h"

#include "struct.h"
#include "run.h"

bool commands_run(
	struct commands* this,
	int dirfd)
{
	bool error = false;
	ENTER;
	
	dpv(this->n);
	
	for (unsigned i = 0, n = this->n; !error && i < n; i++)
	{
		struct command* command = this->data[i];
		
		command_print(command);
		
		if (!cmdln_dry_run)
		{
			error = command_run(command, dirfd);
		}
	}
	
	EXIT;
	return error;
}

