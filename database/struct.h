
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <sys/types.h>

struct database
{
	struct database_header {
		unsigned i, n, cap;
		time_t too_old;
	} header, original_header;
	
	int fd;
};

struct database_record
{
	char name[PATH_MAX];
	dev_t st_dev;
	ino_t st_ino;
	bool passed;
	time_t timestamp;
};


