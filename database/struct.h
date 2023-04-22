
#include <time.h>

struct gdbm_file_info;

struct database
{
	struct gdbm_file_info* gdbm;
	
	time_t now;
	
	time_t clean;
};

