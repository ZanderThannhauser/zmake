
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
			case 'a' ... 'z':
			case 'A' ... 'Z':
			case '`': case '~':
			case '1': case '!':
			case '2': case '@':
			case '3': case '#':
			case '4': case '$':
			case '5': case '%':
			case '6': case '^':
			case '7': case '&':
			case '8': case '*':
			case '9': case '(':
			case '0': case ')':
			case '-': case '_':
			case '=': case '+':
			case '.':
			case '/':
			case ' ':
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














