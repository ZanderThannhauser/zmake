
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>

#include <string.h>

#include <debug.h>

#include <dirfd/struct.h>
#include <dirfd/new.h>
#include <dirfd/inc.h>
#include <dirfd/free.h>

#include "zebu.h"
#include "statement.h"
#include "recursive.h"

void recursive_parse(
	struct database* database,
	struct recipeset* all_recipes,
	struct recipeset* propagate_ftimes,
	struct dirfd* absolute_dirfd,
	struct dirfd* local_dirfd,
	struct scope* scope,
	const char* path)
{
	ENTER;
	
	struct dirfd* new_local_dirfd;
	const char* filename;
	
	char* slash = rindex(path, '/');
	
	if (slash)
	{
		char dirname[PATH_MAX] = {};
		
		memcpy(dirname, path, slash - path);
		
		dpvs(dirname);
		
		new_local_dirfd = new_dirfd(dirname);
		
		filename = slash + 1;
	}
	else
	{
		new_local_dirfd = inc_dirfd(local_dirfd);
		filename = path;
	}
	
	dpvs(filename);
	
	int fd = openat(new_local_dirfd->fd, filename, O_RDONLY);
	
	if (fd < 0)
	{
		TODO;
		exit(1);
	}
	
	FILE* stream = fdopen(fd, "r");
	
	if (!stream)
	{
		TODO;
		exit(1);
	}
	
	struct zebu_$start* start = zebu_parse(stream);
	
	struct zebu_root* root = start->root;
	
	for (unsigned i = 0, n = root->statements.n; i < n; i++)
	{
		struct zebu_statement* statement = root->statements.data[i];
		
		evaluate_statement(
			statement,
			all_recipes, propagate_ftimes,
			database,
			absolute_dirfd, new_local_dirfd,
			scope);
	}
	
	free_dirfd(new_local_dirfd);
	
	free_zebu_$start(start);
	
	fclose(stream);
	
	EXIT;
}




















