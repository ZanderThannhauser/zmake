
#include <debug.h>

#include "resolve.h"

struct path* resolve_path(
	const char* path_ro,
	struct path* relative,
	struct path* absolute)
{
	ENTER;
	
	dpvs(path_ro);
	
	struct path* moving;
	
	if (path_ro[0] == '/')
		moving = absolute;
	else
		moving = relative;
	
	char path[PATH_MAX], *tok = path;
	strcpy(path, path_ro);
	
	for (char* name; (name = strtok_r(NULL, "/", &tok)); )
	{
		dpvs(name);
	}
	
	TODO;
	
	EXIT;
}

