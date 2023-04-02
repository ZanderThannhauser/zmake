
#include <debug.h>

#include "options/targets.h"
#include "free.h"

void cmdln_free()
{
	ENTER;
	
	free(cmdln_targets.data);
	
	EXIT;
}

