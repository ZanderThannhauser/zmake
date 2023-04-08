
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <debug.h>

#include <memory/srealloc.h>

#include <parse/zebu.h>

#include <value/string/new.h>

#include "string.h"

char* escape_zebu_string(
	struct zebu_token* token)
{
	ENTER;
	
	dpvs((char*) token->data);
	
	struct {
		char* data;
		unsigned n, cap;
	} buffer = {};
	
	void append(char c)
	{
		if (buffer.n == buffer.cap)
		{
			buffer.cap = buffer.cap << 1 ?: 1;
			buffer.data = srealloc(buffer.data, sizeof(*buffer.data) * buffer.cap);
		}
		buffer.data[buffer.n++] = c;
	}
	
	const char* moving = (void*) token->data;
	char first = *moving++;
	
	dpvc(first);
	
	while (*moving != first)
	{
		if (*moving != '\\')
		{
			append(*moving++);
		}
		else switch (*++moving)
		{
			case 'n': append('\n'), moving++; break;
			case 't':
				TODO;
				moving++;
				break;
			case 'e':
				TODO;
				moving++;
				break;
			case '\\':
				TODO;
				moving++;
				break;
			case '\"':
				TODO;
				moving++;
				break;
			case '\'':
				TODO;
				moving++;
				break;
			default:
				TODO;
				break;
		}
	}
	
	append(0), buffer.n--;
	
	dpvs(buffer.data);
	
	EXIT;
	return buffer.data;
}

struct value* evaluate_string_expression(
	struct zebu_token* token)
{
	ENTER;
	
	dpvs((char*) token->data);
	
	char* data = escape_zebu_string(token);
	
	struct value* result = new_string_value(data, strlen(data));
	
	free(data);
	
	EXIT;
	return result;
}













