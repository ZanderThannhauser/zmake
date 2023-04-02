
#include <sys/types.h>

struct dirfd
{
	int fd;
	
	dev_t st_dev;
	ino_t st_ino;
	
	unsigned refcount;
};


