
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <debug.h>

#include <defines/argv0.h>

#include <enums/error.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct dirfd* new_dirfd(
	const char* path)
{
	ENTER;
	
	dpvs(path);
	
	struct dirfd* this = smalloc(sizeof(*this));
	
	this->fd = open(path, O_PATH);
	
	if (this->fd < 0)
	{
		fprintf(stderr, "%s: error on open(\"%s\"): %m\n", argv0, path);
		exit(e_syscall_failed);
	}
	
	struct stat buf;
	
	if (fstat(this->fd, &buf) < 0)
	{
		TODO;
		exit(e_syscall_failed);
	}
	
	this->st_dev = buf.st_dev;
	this->st_ino = buf.st_ino;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}














