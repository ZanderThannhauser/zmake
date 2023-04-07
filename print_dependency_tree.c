
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

#include <debug.h>

#include <recipeset/foreach.h>

#include <recipe/struct.h>

#include <misc/hsv_to_rgb.h>

#include "mark_recipes_for_execution.h"
#include "print_dependency_tree.h"

void print_dependency_tree(
	struct recipeset* all_recipes)
{
	ENTER;
	
	FILE* stream = fopen("dependency-tree.dot", "w");
	
	if (!stream)
	{
		TODO;
		exit(1);
	}
	
	fprintf(stream, "digraph {" "\n");
	
	fprintf(stream, ""
		"rankdir = LR;" "\n"
	"");
	
	recipeset_foreach(all_recipes, ({
		void callback(struct recipe* recipe)
		{
			const char* target = recipe->target;
			
			struct dirfd* dirfd = recipe->dirfd;
			
			fprintf(stream, ""
				"\"%s:%p\" [" "\n"
					"label = \"%s\";" "\n"
					"shape = box;" "\n"
					"peripheries = %u;" "\n"
				"];" "\n"
			"",
			target, dirfd,
			target,
			recipe->execution.round == execution_round_id && recipe->execution.marked ? 2 : 1);
			
			recipeset_foreach(recipe->dep_on, ({
				void callback(struct recipe* dependency)
				{
					fprintf(stream, ""
						"\"%s:%p\" -> \"%s:%p\" [" "\n"
						"];" "\n"
					"", target, dirfd, dependency->target, dependency->dirfd);
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


















