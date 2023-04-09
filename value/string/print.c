
#include <assert.h>
#include <stdio.h>

#include <debug.h>

#include "struct.h"
#include "print.h"

void string_value_print(
	struct value* super)
{
	ENTER;
	
	struct string_value* this = (void*) super;
	
	putchar('\"');
	
	dpv(this->len);
	
	for (unsigned i = 0, n = this->len; i < n; i++)
	{
		char c = this->chars[i];
		
		switch (c)
		{
			case '.':
			case '/':
			case '_':
			case '-':
			case 'a' ... 'z':
			case 'A' ... 'Z':
			case '0' ... '9':
				putchar(c);
				break;
			
			default:
			{
				dpvc(c);
				TODO;
				break;
			}
		}
	}
	
	putchar('\"');
	
	EXIT;
}














