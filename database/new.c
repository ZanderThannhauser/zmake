
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <gdbm.h>

#include <debug.h>

#include <defines/argv0.h>

#include <enums/error.h>

#include <memory/smalloc.h>

#include <cmdln/options/always_make.h>

#include "struct.h"
#include "new.h"

struct database* new_database()
{
	ENTER;
	
	struct database* this = smalloc(sizeof(*this));
	
	this->gdbm = gdbm_open(".zmake.db", 0, GDBM_WRCREAT | GDBM_CLOEXEC, 0664, NULL);
	
	if (!this->gdbm)
	{
		fprintf(stderr, "%s: error on gdbm_open(\".zmake.db\"): %s\n",
			argv0, gdbm_strerror(gdbm_errno));
		exit(e_syscall_failed);
	}
	
	this->now = time(NULL);
	
	{
		char key[] = "\0" "last-clean" "\0";
		
		if (cmdln_always_make)
		{
			this->clean = time(NULL);
			
			if (gdbm_store(
				/* handle: */ this->gdbm,
				/* key: */ (datum) {(char*) &key, sizeof(key)},
				/* content: */ (datum) {(char*) &this->clean, sizeof(this->clean)},
				/* flag: */ GDBM_REPLACE) < 0)
			{
				TODO;
				exit(1);
			}
		}
		else
		{
			datum content = gdbm_fetch(this->gdbm, (datum) {key, sizeof(key)});
			
			if (content.dptr)
			{
				this->clean = *((time_t*) content.dptr);
			}
			else if (gdbm_errno == GDBM_ITEM_NOT_FOUND)
			{
				this->clean = 0;
			}
			else
			{
				fprintf(stderr, "%s: error on gdbm_fetch(): %s\n",
					argv0, gdbm_db_strerror(this->gdbm)),
				exit(e_syscall_failed);
			}
			
			free(content.dptr);
		}
	}
	
	EXIT;
	return this;
}




















