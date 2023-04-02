
struct recipeset;

struct recipe* recipeset_lookup(
	const struct recipeset* this,
	const char* target,
	struct dirfd* dirfd);
