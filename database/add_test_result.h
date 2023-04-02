
struct database;

void database_add_test_result(
	struct database* this,
	const char* target,
	bool has_passed);
