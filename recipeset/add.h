
#include <stdbool.h>

struct recipeset;
struct recipe;

bool recipeset_add(
	struct recipeset* this,
	struct recipe* recipe);
