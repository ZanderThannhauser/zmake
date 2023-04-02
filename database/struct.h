
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
	bool passed;
	time_t timestamp;
};


