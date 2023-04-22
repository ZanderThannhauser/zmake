
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <gdbm.h>

#include <debug.h>

#include <defines/argv0.h>

#include <enums/error.h>

#include <dirfd/struct.h>

#include "struct.h"
#include "lookup.h"

time_t database_lookup(
	struct database* this,
	const char* target,
	struct dirfd* dirfd)
{
	time_t ftime;
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
	
	datum content = gdbm_fetch(this->gdbm, (datum) {(char*) &key, sizeof(key)});
	
	if (content.dptr)
	{
		ftime = *((time_t*) content.dptr);
	}
	else if (gdbm_errno == GDBM_ITEM_NOT_FOUND)
	{
		ftime = this->now;
		
		if (gdbm_store(
			/* handle: */ this->gdbm,
			/* key: */ (datum) {(char*) &key, sizeof(key)},
			/* content: */ (datum) {(char*) &ftime, sizeof(ftime)},
			/* flag: */ GDBM_REPLACE) < 0)
		{
			TODO;
			exit(1);
		}
	}
	else
	{
		fprintf(stderr, "%s: error on gdbm_fetch(): %s\n", argv0, gdbm_db_strerror(this->gdbm)),
		exit(e_syscall_failed);
	}
	
	dpv(ftime);
	
	free(content.dptr);
	
	EXIT;
	return ftime;
}











