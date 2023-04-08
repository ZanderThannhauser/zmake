
#include <assert.h>
#include <stdio.h>

#include <debug.h>

#include "struct.h"
#include "print.h"

void boolean_value_print(
	struct value* super)
{
	ENTER;
	
	TODO;
	#if 0
	struct boolean_value* this = (void*) super;
	
	putchar('\"');
	
	dpv(this->len);
	
	for (unsigned i = 0, n = this->len; i < n; i++)
	{
		char c = this->chars[i];
		
		switch (c)
		{
			case 'a' ... 'z':
			case 'A' ... 'Z':
			case '0' ... '9':
				putchar(c);
				break;
			
			default:
				TODO;
				break;
		}
	}
	
	putchar('\"');
	#endif
	
	EXIT;
}

