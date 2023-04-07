
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
		fprintf(stderr, "%s: error on gdbm_open(\".zmake.db\"): %s\n", argv0, gdbm_strerror(gdbm_errno));
		exit(e_syscall_failed);
	}
	
	this->now = time(NULL);
	
	if (cmdln_always_make)
	{
		TODO;
	}
	
	EXIT;
	return this;
}








