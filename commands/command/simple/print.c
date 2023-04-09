
#include <stdio.h>

#include "struct.h"
#include "print.h"

void simple_command_print(
	struct simple_command* this)
{
	for (unsigned i = 0, n = this->args.n; i < n; i++)
	{
		printf("%s", this->args.data[i]);
		
		if (i + 1 < n)
			putchar(' ');
	}
}

