
#include <stdlib.h>

#include <debug.h>

#include "options/makefiles.h"

#include "free.h"

void cmdln_free()
{
	ENTER;
	
	for (int i = 0, n = cmdln_makefiles.n; i < n; i++)
	{
		struct cmdln_makefile_bundle* bundle = &cmdln_makefiles.data[i];
		
		free(bundle->targets.data);
		free(bundle->makefiles.data);
	}
	
	free(cmdln_makefiles.data);
	
	EXIT;
}










