
/*#include <dirfd/struct.h>*/


/*#include <recipeset/add.h>*/
/*#include <recipeset/lookup.h>*/
/*#include <recipeset/free.h>*/

/*#include <recipe/new.h>*/
/*#include <recipe/add_depenency.h>*/
/*#include <recipe/free.h>*/

/*#include "evaluate/statement/root.h"*/

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>

#include <debug.h>

#include <recipe/compare_scores.h>

#include <recipeset/new.h>
#include <recipeset/len.h>
#include <recipeset/free.h>

#include <propagate_ftimes.h>

#include "parse.h"
#include "recursive.h"

void parse(
	struct recipeset* all_recipes,
	struct database* database,
	struct dirfd* dirfd,
	struct scope* scope,
	const char* path)
{
	ENTER;
	
	struct recipeset* propagate_ftimes_start = new_recipeset(false);
	
	recursive_parse(
		/* struct database* database: */ database,
		/* struct recipeset* all_recipes: */ all_recipes,
		/* struct recipeset* propagate_ftimes: */ propagate_ftimes_start,
		/* struct dirfd* absolute_dirfd: */ dirfd,
		/* struct dirfd* local_dirfd: */ dirfd,
		/* struct scope* scope: */ scope,
		/* const char* path: */ path);
	
	if (recipeset_len(propagate_ftimes_start))
		propagate_ftimes(propagate_ftimes_start);
	
	free_recipeset(propagate_ftimes_start);
	
	EXIT;
}



































