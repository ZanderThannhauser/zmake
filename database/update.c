
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <gdbm.h>
#include <debug.h>

#include <dirfd/struct.h>

#include "struct.h"
#include "update.h"

void database_update(
	struct database* this,
	const char* target,
	struct dirfd* dirfd)
{
	ENTER;
	
	dpvs(target);
	
	struct {
		char target[PATH_MAX];
		dev_t dev;
		ino_t ino;
	} key;
	
	memset(key.target, 0, sizeof(key.target));
	strcpy(key.target, target);
	key.dev = dirfd->dev;
	key.ino = dirfd->ino;
	
	time_t ftime = time(NULL);
	
	dpv(ftime);
	
	if (gdbm_store(
		/* handle: */ this->gdbm,
		/* key: */ (datum) {(char*) &key, sizeof(key)},
		/* content: */ (datum) {(char*) &ftime, sizeof(ftime)},
		/* flag: */ GDBM_REPLACE) < 0)
	{
		TODO;
		exit(1);
	}
	
	EXIT;
}





