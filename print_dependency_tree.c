
#include <debug.h>

#include <recipeset/foreach.h>

#include <recipe/struct.h>

#include "print_dependency_tree.h"

void print_dependency_tree(
	int dirfd,
	struct recipeset* all_recipes)
{
	ENTER;
	
	int fd = openat(dirfd, "dependency-tree.dot",
		O_WRONLY | O_TRUNC | O_CREAT, 0664);
	
	if (fd < 0)
	{
		TODO;
		exit(1);
	}
	
	FILE* stream = fdopen(fd, "w");
	
	if (!stream)
	{
		TODO;
		exit(1);
	}
	
	fprintf(stream, "digraph {" "\n");
	
	fprintf(stream, ""
		"rankdir = BT;" "\n"
	"");
	
	fprintf(stream, ""
		"node [" "\n"
			"shape = box;" "\n"
		"]" "\n"
	"");
	
	recipeset_foreach(all_recipes, ({
		void callback(struct recipe* recipe)
		{
			const char* target = recipe->target;
			
			fprintf(stream, ""
				"%s [" "\n"
					"label = \"%s\";" "\n"
				"];" "\n"
			"", target, target);
			
			recipeset_foreach(recipe->dep_on, ({
				void callback(struct recipe* dependency)
				{
					fprintf(stream, ""
						"%s -> %s [" "\n"
						"];" "\n"
					"", target, dependency->target);
				}
				callback;
			}));
		}
		callback;
	}));
	
	fprintf(stream, "}" "\n");
	
	fclose(stream);
	
	EXIT;
}


















