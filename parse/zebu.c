#include "zebu.h"

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <limits.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

const unsigned zebu_shifts[24][7] = {
	[1][2] = 2,
	[1][3] = 3,
	[2][4] = 6,
	[3][2] = 2,
	[3][3] = 3,
	[4][2] = 2,
	[4][3] = 8,
	[6][2] = 11,
	[6][3] = 12,
	[8][2] = 2,
	[8][3] = 8,
	[10][2] = 2,
	[10][3] = 8,
	[11][2] = 11,
	[11][3] = 12,
	[12][6] = 17,
	[17][2] = 20,
	[18][6] = 17,
	[20][2] = 23,
	[20][3] = 24,
	[22][6] = 17,
	[23][2] = 23,
	[23][3] = 24,
};


const unsigned zebu_reduces[28][7] = {
	[4][5] = 1,
	[5][5] = 2,
	[7][5] = 3,
	[8][5] = 4,
	[9][5] = 5,
	[10][5] = 6,
	[12][2] = 7,
	[12][3] = 7,
	[12][5] = 7,
	[13][2] = 8,
	[13][3] = 8,
	[13][5] = 8,
	[14][5] = 9,
	[15][5] = 10,
	[16][2] = 11,
	[16][3] = 11,
	[16][5] = 11,
	[18][2] = 12,
	[18][3] = 12,
	[18][5] = 12,
	[19][2] = 13,
	[19][3] = 13,
	[19][5] = 13,
	[21][2] = 14,
	[21][3] = 14,
	[21][5] = 14,
	[22][2] = 15,
	[22][3] = 15,
	[22][5] = 15,
	[24][2] = 16,
	[24][3] = 16,
	[24][5] = 16,
	[24][6] = 16,
	[25][2] = 17,
	[25][3] = 17,
	[25][5] = 17,
	[25][6] = 17,
	[26][2] = 18,
	[26][3] = 18,
	[26][5] = 18,
	[27][2] = 19,
	[27][3] = 19,
	[27][5] = 19,
	[27][6] = 19,
};


const unsigned zebu_gotos[24][9] = {
	[1][1] = 4,
	[1][2] = 5,
	[3][1] = 4,
	[3][2] = 7,
	[4][1] = 10,
	[4][3] = 9,
	[6][4] = 13,
	[8][1] = 10,
	[8][3] = 14,
	[10][1] = 10,
	[10][3] = 15,
	[11][4] = 16,
	[12][5] = 18,
	[12][6] = 19,
	[18][5] = 22,
	[18][7] = 21,
	[20][8] = 25,
	[22][5] = 22,
	[22][7] = 26,
	[23][8] = 27,
};


const unsigned zebu_lexer_starts[28] = {
	[1] = 1,
	[2] = 2,
	[3] = 1,
	[4] = 3,
	[5] = 4,
	[6] = 1,
	[7] = 4,
	[8] = 3,
	[9] = 4,
	[10] = 3,
	[11] = 1,
	[12] = 5,
	[13] = 3,
	[14] = 4,
	[15] = 4,
	[16] = 3,
	[17] = 6,
	[18] = 5,
	[19] = 3,
	[20] = 1,
	[21] = 3,
	[22] = 5,
	[23] = 1,
	[24] = 5,
	[25] = 5,
	[26] = 3,
	[27] = 5,
};


const unsigned zebu_lexer[10][123] = {
	[1][10] = 7,
	[1][32] = 8,
	[1][48] = 9,
	[1][49] = 9,
	[1][50] = 9,
	[1][51] = 9,
	[1][52] = 9,
	[1][53] = 9,
	[1][54] = 9,
	[1][55] = 9,
	[1][56] = 9,
	[1][57] = 9,
	[1][97] = 9,
	[1][98] = 9,
	[1][99] = 9,
	[1][100] = 9,
	[1][101] = 9,
	[1][102] = 9,
	[1][103] = 9,
	[1][104] = 9,
	[1][105] = 9,
	[1][106] = 9,
	[1][107] = 9,
	[1][108] = 9,
	[1][109] = 9,
	[1][110] = 9,
	[1][111] = 9,
	[1][112] = 9,
	[1][113] = 9,
	[1][114] = 9,
	[1][115] = 9,
	[1][116] = 9,
	[1][117] = 9,
	[1][118] = 9,
	[1][119] = 9,
	[1][120] = 9,
	[1][121] = 9,
	[1][122] = 9,
	[2][32] = 8,
	[2][58] = 10,
	[3][10] = 7,
	[3][32] = 8,
	[3][48] = 9,
	[3][49] = 9,
	[3][50] = 9,
	[3][51] = 9,
	[3][52] = 9,
	[3][53] = 9,
	[3][54] = 9,
	[3][55] = 9,
	[3][56] = 9,
	[3][57] = 9,
	[3][97] = 9,
	[3][98] = 9,
	[3][99] = 9,
	[3][100] = 9,
	[3][101] = 9,
	[3][102] = 9,
	[3][103] = 9,
	[3][104] = 9,
	[3][105] = 9,
	[3][106] = 9,
	[3][107] = 9,
	[3][108] = 9,
	[3][109] = 9,
	[3][110] = 9,
	[3][111] = 9,
	[3][112] = 9,
	[3][113] = 9,
	[3][114] = 9,
	[3][115] = 9,
	[3][116] = 9,
	[3][117] = 9,
	[3][118] = 9,
	[3][119] = 9,
	[3][120] = 9,
	[3][121] = 9,
	[3][122] = 9,
	[4][32] = 8,
	[5][9] = 12,
	[5][10] = 7,
	[5][32] = 8,
	[5][48] = 9,
	[5][49] = 9,
	[5][50] = 9,
	[5][51] = 9,
	[5][52] = 9,
	[5][53] = 9,
	[5][54] = 9,
	[5][55] = 9,
	[5][56] = 9,
	[5][57] = 9,
	[5][97] = 9,
	[5][98] = 9,
	[5][99] = 9,
	[5][100] = 9,
	[5][101] = 9,
	[5][102] = 9,
	[5][103] = 9,
	[5][104] = 9,
	[5][105] = 9,
	[5][106] = 9,
	[5][107] = 9,
	[5][108] = 9,
	[5][109] = 9,
	[5][110] = 9,
	[5][111] = 9,
	[5][112] = 9,
	[5][113] = 9,
	[5][114] = 9,
	[5][115] = 9,
	[5][116] = 9,
	[5][117] = 9,
	[5][118] = 9,
	[5][119] = 9,
	[5][120] = 9,
	[5][121] = 9,
	[5][122] = 9,
	[6][32] = 8,
	[6][48] = 9,
	[6][49] = 9,
	[6][50] = 9,
	[6][51] = 9,
	[6][52] = 9,
	[6][53] = 9,
	[6][54] = 9,
	[6][55] = 9,
	[6][56] = 9,
	[6][57] = 9,
	[6][97] = 9,
	[6][98] = 9,
	[6][99] = 9,
	[6][100] = 9,
	[6][101] = 9,
	[6][102] = 9,
	[6][103] = 9,
	[6][104] = 9,
	[6][105] = 9,
	[6][106] = 9,
	[6][107] = 9,
	[6][108] = 9,
	[6][109] = 9,
	[6][110] = 9,
	[6][111] = 9,
	[6][112] = 9,
	[6][113] = 9,
	[6][114] = 9,
	[6][115] = 9,
	[6][116] = 9,
	[6][117] = 9,
	[6][118] = 9,
	[6][119] = 9,
	[6][120] = 9,
	[6][121] = 9,
	[6][122] = 9,
	[8][32] = 8,
	[9][48] = 9,
	[9][49] = 9,
	[9][50] = 9,
	[9][51] = 9,
	[9][52] = 9,
	[9][53] = 9,
	[9][54] = 9,
	[9][55] = 9,
	[9][56] = 9,
	[9][57] = 9,
	[9][97] = 9,
	[9][98] = 9,
	[9][99] = 9,
	[9][100] = 9,
	[9][101] = 9,
	[9][102] = 9,
	[9][103] = 9,
	[9][104] = 9,
	[9][105] = 9,
	[9][106] = 9,
	[9][107] = 9,
	[9][108] = 9,
	[9][109] = 9,
	[9][110] = 9,
	[9][111] = 9,
	[9][112] = 9,
	[9][113] = 9,
	[9][114] = 9,
	[9][115] = 9,
	[9][116] = 9,
	[9][117] = 9,
	[9][118] = 9,
	[9][119] = 9,
	[9][120] = 9,
	[9][121] = 9,
	[9][122] = 9,
};


const unsigned zebu_lexer_accepts[13] = {
	[7] = 3,
	[8] = 1,
	[9] = 2,
	[10] = 4,
	[11] = 5,
	[12] = 6,
};


const unsigned zebu_lexer_EOFs[6] = {
	[3] = 11,
	[4] = 11,
	[5] = 11,
};


#ifdef ZEBU_DEBUG
#include <stdbool.h>

struct link
{
    bool is_last;
    struct link* prev;
};

static void print_links(struct link* link)
{
    if (!link) return;
    print_links(link->prev);
    fputs(link->is_last ? "    " : "│   ", stdout);
}

static void print_tree_escape(char *out, char in)
{
    switch (in)
    {
        case ' ':
        case '~':
        case '!':
        case '@':
        case '#':
        case '$':
        case '%':
        case '^':
        case '&':
        case '*':
        case '-':
        case '+':
        case '=':
        case '|':
        case '<': case '>':
        case '(': case ')':
        case '{': case '}':
        case '[': case ']':
        case ':': case ';':
        case ',': case '.':
        case '_':
        case '/':
        case '`':
        case '0' ... '9':
        case 'a' ... 'z':
        case 'A' ... 'Z':
            *out++ = in;
            *out = 0;
            break;
        
        case '\\': *out++ = '\\', *out++ = '\\', *out = 0; break;
        
        case '\'': *out++ = '\\', *out++ = '\'', *out = 0; break;
        
        case '\"': *out++ = '\\', *out++ = '\"', *out = 0; break;
        
        case '\t': *out++ = '\\', *out++ = 't', *out = 0; break;
        
        case '\n': *out++ = '\\', *out++ = 'n', *out = 0; break;
        
        default:
            sprintf(out, "\\x%02X", in);
            break;
    }
}

enum prefix
{
p_root,
p_not_last_child,
p_last_child,
};

void print_token_leaf(struct link* links, enum prefix p, const char* name, struct zebu_token* token)
{
print_links(links);
switch (p)
{
case p_root: break;
case p_not_last_child: fputs("├── ", stdout); break;
case p_last_child: fputs("└── ", stdout); break;
}
printf("\e[32m%s\e[0m (\e[35m\"", name);
char escape[10];
for (unsigned i = 0, n = token->len; i < n; i++)
print_tree_escape(escape, token->data[i]), fputs(escape, stdout);
printf("\"\e[0m)");
#if ZEBU_LINE_NUMBERS
printf(" on line %u", token->line);
#endif
printf("\n");
}

void print_scanf_leaf(struct link* links, enum prefix p, const char* name, const char* format, ...)
{
va_list ap;
print_links(links);
switch (p)
{
case p_root: break;
case p_not_last_child: fputs("├── ", stdout); break;
case p_last_child: fputs("└── ", stdout); break;
}
printf("\e[32m%s\e[0m (\e[35m%s\e[m: \e[35m", name, format);
va_start(ap, format);
vprintf(format, ap);
va_end(ap);
printf("\e[0m)\n");
}

void print_empty_leaf(struct link* links, enum prefix p, const char* type, const char* name)
{
print_links(links);
switch (p)
{
case p_root: break;
case p_not_last_child: fputs("├── ", stdout); break;
case p_last_child: fputs("└── ", stdout); break;
}
printf("\e[31m%s\e[0m (\e[36m%s\e[0m)\n", name, type);
}
void print_zebu_$start(struct link* links, enum prefix p, const char* name, struct zebu_$start* ptree);

void print_zebu_command(struct link* links, enum prefix p, const char* name, struct zebu_command* ptree);

void print_zebu_commands(struct link* links, enum prefix p, const char* name, struct zebu_commands* ptree);

void print_zebu_recipe(struct link* links, enum prefix p, const char* name, struct zebu_recipe* ptree);

void print_zebu_root(struct link* links, enum prefix p, const char* name, struct zebu_root* ptree);

void print_zebu_$start(struct link* links, enum prefix p, const char* name, struct zebu_$start* ptree)
{
print_links(links);

struct link* new = NULL;

switch (p)
{
case p_root:
break;

case p_not_last_child:
fputs("├── ", stdout);
new = malloc(sizeof(*new));
new->is_last = false;
new->prev = links;
break;

case p_last_child:
fputs("└── ", stdout);
new = malloc(sizeof(*new));
new->is_last = true;
new->prev = links;
break;
}
printf("\e[34m%s\e[m (\e[36m$start\e[m)", name);
#if ZEBU_LINE_NUMBERS
printf(" on line %u through %u", ptree->startline, ptree->endline);
#endif
printf("\n");
if (ptree->root)
print_zebu_root(new ?: links, p_last_child, "root", ptree->root);
else
print_empty_leaf(new ?: links, p_last_child, "root", "root");
free(new);
}
void print_zebu_command(struct link* links, enum prefix p, const char* name, struct zebu_command* ptree)
{
print_links(links);

struct link* new = NULL;

switch (p)
{
case p_root:
break;

case p_not_last_child:
fputs("├── ", stdout);
new = malloc(sizeof(*new));
new->is_last = false;
new->prev = links;
break;

case p_last_child:
fputs("└── ", stdout);
new = malloc(sizeof(*new));
new->is_last = true;
new->prev = links;
break;
}
printf("\e[34m%s\e[m (\e[36mcommand\e[m)", name);
#if ZEBU_LINE_NUMBERS
printf(" on line %u through %u", ptree->startline, ptree->endline);
#endif
printf("\n");
if (ptree->args.n)
{
for (unsigned i = 0, n = ptree->args.n; i < n; i++)
{
char label[4 + 30];
snprintf(label, sizeof(label), "args[%u]", i);
print_token_leaf(new ?: links, i + 1 < n ? p_not_last_child : p_last_child, label, ptree->args.data[i]);
}
}
else
{
print_empty_leaf(new ?: links, p_last_child, "token[]", "args");
}
free(new);
}
void print_zebu_commands(struct link* links, enum prefix p, const char* name, struct zebu_commands* ptree)
{
print_links(links);

struct link* new = NULL;

switch (p)
{
case p_root:
break;

case p_not_last_child:
fputs("├── ", stdout);
new = malloc(sizeof(*new));
new->is_last = false;
new->prev = links;
break;

case p_last_child:
fputs("└── ", stdout);
new = malloc(sizeof(*new));
new->is_last = true;
new->prev = links;
break;
}
printf("\e[34m%s\e[m (\e[36mcommands\e[m)", name);
#if ZEBU_LINE_NUMBERS
printf(" on line %u through %u", ptree->startline, ptree->endline);
#endif
printf("\n");
if (ptree->commands.n)
{
for (unsigned i = 0, n = ptree->commands.n; i < n; i++)
{
char label[8 + 30];
snprintf(label, sizeof(label), "commands[%u]", i);
print_zebu_command(new ?: links, i + 1 < n ? p_not_last_child : p_last_child, label, ptree->commands.data[i]);
}
}
else
{
print_empty_leaf(new ?: links, p_last_child, "command[]", "commands");
}
free(new);
}
void print_zebu_recipe(struct link* links, enum prefix p, const char* name, struct zebu_recipe* ptree)
{
print_links(links);

struct link* new = NULL;

switch (p)
{
case p_root:
break;

case p_not_last_child:
fputs("├── ", stdout);
new = malloc(sizeof(*new));
new->is_last = false;
new->prev = links;
break;

case p_last_child:
fputs("└── ", stdout);
new = malloc(sizeof(*new));
new->is_last = true;
new->prev = links;
break;
}
printf("\e[34m%s\e[m (\e[36mrecipe\e[m)", name);
#if ZEBU_LINE_NUMBERS
printf(" on line %u through %u", ptree->startline, ptree->endline);
#endif
printf("\n");
if (ptree->commands)
print_zebu_commands(new ?: links, p_not_last_child, "commands", ptree->commands);
else
print_empty_leaf(new ?: links, p_not_last_child, "commands", "commands");
if (ptree->depenencies.n)
{
for (unsigned i = 0, n = ptree->depenencies.n; i < n; i++)
{
char label[11 + 30];
snprintf(label, sizeof(label), "depenencies[%u]", i);
print_token_leaf(new ?: links, i + 1 < n ? p_not_last_child : p_not_last_child, label, ptree->depenencies.data[i]);
}
}
else
{
print_empty_leaf(new ?: links, p_not_last_child, "token[]", "depenencies");
}
if (ptree->target)
print_token_leaf(new ?: links, p_last_child, "target", ptree->target);
else
print_empty_leaf(new ?: links, p_last_child, "token", "target");
free(new);
}
void print_zebu_root(struct link* links, enum prefix p, const char* name, struct zebu_root* ptree)
{
print_links(links);

struct link* new = NULL;

switch (p)
{
case p_root:
break;

case p_not_last_child:
fputs("├── ", stdout);
new = malloc(sizeof(*new));
new->is_last = false;
new->prev = links;
break;

case p_last_child:
fputs("└── ", stdout);
new = malloc(sizeof(*new));
new->is_last = true;
new->prev = links;
break;
}
printf("\e[34m%s\e[m (\e[36mroot\e[m)", name);
#if ZEBU_LINE_NUMBERS
printf(" on line %u through %u", ptree->startline, ptree->endline);
#endif
printf("\n");
if (ptree->recipes.n)
{
for (unsigned i = 0, n = ptree->recipes.n; i < n; i++)
{
char label[7 + 30];
snprintf(label, sizeof(label), "recipes[%u]", i);
print_zebu_recipe(new ?: links, i + 1 < n ? p_not_last_child : p_last_child, label, ptree->recipes.data[i]);
}
}
else
{
print_empty_leaf(new ?: links, p_last_child, "recipe[]", "recipes");
}
free(new);
}

#endif

struct zebu_token* inc_zebu_token(struct zebu_token* token)
{
	if (token) token->refcount++;
	return token;
}
struct zebu_$start* inc_zebu_$start(struct zebu_$start* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct zebu_command* inc_zebu_command(struct zebu_command* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct zebu_commands* inc_zebu_commands(struct zebu_commands* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct zebu_recipe* inc_zebu_recipe(struct zebu_recipe* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct zebu_root* inc_zebu_root(struct zebu_root* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}



extern void free_zebu_token(struct zebu_token* token);
extern void free_zebu_$start(struct zebu_$start* ptree);

extern void free_zebu_command(struct zebu_command* ptree);

extern void free_zebu_commands(struct zebu_commands* ptree);

extern void free_zebu_recipe(struct zebu_recipe* ptree);

extern void free_zebu_root(struct zebu_root* ptree);

void free_zebu_token(struct zebu_token* token)
{
	if (token && !--token->refcount)
	{
		free(token->data);
		free(token);
	}
}
void free_zebu_$start(struct zebu_$start* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_zebu_root(ptree->root);
		free(ptree);
	}
}

void free_zebu_command(struct zebu_command* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		for (unsigned i = 0, n = ptree->args.n; i < n; i++)
			free_zebu_token(ptree->args.data[i]);
		free(ptree->args.data);
		free(ptree);
	}
}

void free_zebu_commands(struct zebu_commands* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		for (unsigned i = 0, n = ptree->commands.n; i < n; i++)
			free_zebu_command(ptree->commands.data[i]);
		free(ptree->commands.data);
		free(ptree);
	}
}

void free_zebu_recipe(struct zebu_recipe* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_zebu_commands(ptree->commands);
		for (unsigned i = 0, n = ptree->depenencies.n; i < n; i++)
			free_zebu_token(ptree->depenencies.data[i]);
		free(ptree->depenencies.data);
		free_zebu_token(ptree->target);
		free(ptree);
	}
}

void free_zebu_root(struct zebu_root* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		for (unsigned i = 0, n = ptree->recipes.n; i < n; i++)
			free_zebu_recipe(ptree->recipes.data[i]);
		free(ptree->recipes.data);
		free(ptree);
	}
}



#define argv0 (program_invocation_name)

#define N(array) (sizeof(array) / sizeof(*array))

#ifdef ZEBU_DEBUG
static void escape(char *out, unsigned char in)
{
	switch (in)
	{
		case ' ':
		case '~':
		case '!':
		case '@':
		case '#':
		case '$':
		case '%':
		case '^':
		case '&':
		case '*':
		case '-':
		case '+':
		case '=':
		case '|':
		case '/':
		case '<': case '>':
		case '(': case ')':
		case '{': case '}':
		case '[': case ']':
		case ':': case ';':
		case ',': case '.':
		case '_':
		case '0' ... '9':
		case 'a' ... 'z':
		case 'A' ... 'Z':
			*out++ = in;
			*out = 0;
			break;
		
		case '\\': *out++ = '\\', *out++ = '\\', *out = 0; break;
		
		case '\'': *out++ = '\\', *out++ = '\'', *out = 0; break;
		
		case '\"': *out++ = '\\', *out++ = '\"', *out = 0; break;
		
		case '\t': *out++ = '\\', *out++ = 't', *out = 0; break;
		
		case '\n': *out++ = '\\', *out++ = 'n', *out = 0; break;
		
		default:
			sprintf(out, "\\x%02hhX", in);
			break;
	}
}
#endif

struct zebu_$start* zebu_parse(FILE* stream)
{
	void* root;
	struct { unsigned* data, n, cap; } yacc = {};
	struct { void** data; unsigned n, cap; } data = {};
	struct { unsigned char* data; unsigned n, cap, line; } lexer = {
		.line = 1,
	};
	
	void push_state(unsigned y)
	{
		if (yacc.n + 1 >= yacc.cap)
		{
			yacc.cap = yacc.cap << 1 ?: 1;
			yacc.data = realloc(yacc.data, sizeof(*yacc.data) * yacc.cap);
		}
		yacc.data[yacc.n++] = y;
	}
	
	void push_data(void* d)
	{
		if (data.n + 1 >= data.cap)
		{
			data.cap = data.cap << 1 ?: 1;
			data.data = realloc(data.data, sizeof(*data.data) * data.cap);
		}
		data.data[data.n++] = d;
	}
	
	#ifdef ZEBU_DEBUG
	void ddprintf(const char* fmt, ...)
	{
		for (unsigned i = 0, n = yacc.n; i < n; i++)
			printf("%u ", yacc.data[i]);
		
		printf("| ");
		
		va_list va;
		va_start(va, fmt);
		vprintf(fmt, va);
		va_end(va);
	}
	#endif
	
	void push_char(unsigned char c)
	{
		while (lexer.n + 1 >= lexer.cap)
		{
			lexer.cap = lexer.cap << 1 ?: 1;
			#ifdef ZEBU_DEBUG
			ddprintf("lexer.cap == %u\n", lexer.cap);
			#endif
			lexer.data = realloc(lexer.data, lexer.cap);
		}
		
		lexer.data[lexer.n++] = c;
	}
	
	unsigned y, t, s, r;
	void* td;
	
	void read_token(unsigned l)
	{
		unsigned original_l = l, i = 0, a, b, c, f = 0;
		
		unsigned line = lexer.line;
		
		t = 0;
		
		#ifdef ZEBU_DEBUG
		ddprintf("lexer: \"%.*s\": l = %u\n", lexer.n, lexer.data, l);
		#endif
		
		while (1)
		{
			if (i < lexer.n)
			{
				c = lexer.data[i];
				
				#ifdef ZEBU_DEBUG
				char escaped[10];
				
				escape(escaped, c);
				
				ddprintf("lexer: c = '%s' (0x%X) (from cache)\n", escaped, c);
				#endif
				
				a = l < N(zebu_lexer) && c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0;
			}
			else if ((c = getc(stream)) != EOF)
			{
				push_char(c);
				
				#ifdef ZEBU_DEBUG
				char escaped[10];
				
				escape(escaped, c);
				
				ddprintf("lexer: c = '%s' (0x%X)\n", escaped, c);
				#endif
				
				a = l < N(zebu_lexer) && c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0;
			}
			else
			{
				c = EOF;
				
				#ifdef ZEBU_DEBUG
				ddprintf("lexer: c = <EOF>\n");
				#endif
				
				a = l < N(zebu_lexer_EOFs) ? zebu_lexer_EOFs[l] : 0;
			}
			
			b = l < N(zebu_lexer_accepts) ? zebu_lexer_accepts[l] : 0;
			
			#ifdef ZEBU_DEBUG
			ddprintf("lexer: \"%.*s\" (%u): a = %u, b = %u\n", lexer.n, lexer.data, i, a, b);
			#endif
			
			if (a)
			{
				if (b)
				{
					l = a, t = b, f = i++, lexer.line = line;
					#ifdef ZEBU_DEBUG
					ddprintf("lexer: l = %u\n", l);
					#endif
				}
				else
				{
					l = a, i++;
					#ifdef ZEBU_DEBUG
					ddprintf("lexer: l = %u\n", l);
					#endif
				}
				
				if (c == '\n')
				{
					line++;
					#ifdef ZEBU_DEBUG
					ddprintf("lexer: line: %u\n", line);
					#endif
				}
			}
			else if (b)
			{
				#ifdef ZEBU_DEBUG
				ddprintf("lexer: token: \"%.*s\", line: %u\n", i, lexer.data, line);
				#endif
				
				if (!lexer.n)
				{
					#ifdef ZEBU_DEBUG
					ddprintf("lexer: EOF.\n");
					#endif
					t = b, td = NULL;
					break;
				}
				else if (b == 1)
				{
					#ifdef ZEBU_DEBUG
					ddprintf("lexer: whitespace: \"%.*s\"\n", i, lexer.data);
					#endif
					
					l = original_l, t = 0, lexer.line = line;
					memmove(lexer.data, lexer.data + i, lexer.n - i), lexer.n -= i, i = 0;
				}
				else
				{
					#ifdef ZEBU_DEBUG
					ddprintf("lexer: i = %u\n", i);
					#endif
					
					struct zebu_token* token = malloc(sizeof(*token));
					token->refcount = 1;
					token->line = line;
					token->data = memcpy(malloc(i + 1), lexer.data, i);
					token->data[i] = 0;
					token->len = i;
					t = b, td = token;
					
					lexer.line = line;
					memmove(lexer.data, lexer.data + i, lexer.n - i), lexer.n -= i;
					break;
				}
			}
			else if (t)
			{
				if (t == 1)
				{
					#ifdef ZEBU_DEBUG
					ddprintf("lexer: falling back to whitespace: \"%.*s\"\n", f, lexer.data);
					#endif
					
					l = original_l, t = 0, line = lexer.line;
					memmove(lexer.data, lexer.data + f, lexer.n - f), lexer.n -= f, f = 0, i = 0;
				}
				else
				{
					#ifdef ZEBU_DEBUG
					ddprintf("lexer: falling back to token: \"%.*s\"\n", f, lexer.data);
					#endif
					
					struct zebu_token* token = malloc(sizeof(*token));
					token->refcount = 1;
					token->line = lexer.line;
					token->data = memcpy(malloc(f + 1), lexer.data, f);
					token->data[f] = 0;
					token->len = f;
					td = token;
					
					memmove(lexer.data, lexer.data + f, lexer.n - f), lexer.n -= f, f = 0;
					break;
				}
			}
			else
			{
				if (i != 0)
				{
					if (c == (unsigned) EOF)
						fprintf(stderr, "%s: unexpected '<EOF>' when reading '%.*s' on line %u!\n", argv0, i, lexer.data, line);
					else
						fprintf(stderr, "%s: unexpected '%c' when reading '%.*s' on line %u!\n", argv0, c, i, lexer.data, line);
				}
				else
				{
					if (c == (unsigned) EOF)
						fprintf(stderr, "%s: unexpected '<EOF>' on line %u!\n", argv0, line);
					else
						fprintf(stderr, "%s: unexpected '%c' on line %u!\n", argv0, c, line);
				}
				exit(1);
			}
		}
	}
	
	push_state(1), y = 1, read_token(1);
	
	#ifdef ZEBU_DEBUG
	ddprintf("y = %u, t = %u\n", y, t);
	#endif
	
	while (yacc.n)
	{
		if (y < N(zebu_shifts) && t < N(*zebu_shifts) && (s = zebu_shifts[y][t]))
		{
			#ifdef ZEBU_DEBUG
			ddprintf("s == %u\n", s);
			#endif
			
			y = s, push_state(y), push_data(td);
			
			read_token(zebu_lexer_starts[y]);
			
			#ifdef ZEBU_DEBUG
			ddprintf("t = %u\n", t);
			#endif
		}
		else if (y < N( zebu_reduces) && t < N(*zebu_reduces) && (r = zebu_reduces[y][t]))
		{
			#ifdef ZEBU_DEBUG
			ddprintf("r == %u\n", r);
			#endif
			
			unsigned g;
			void* d;
			
			switch (r)
{
case 2:
{
struct zebu_$start* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_root* subgrammar = data.data[--yacc.n, --data.n];
if (subgrammar->startline < value->startline) value->startline = subgrammar->startline;
if (value->endline < subgrammar->endline) value->endline = subgrammar->endline;
free_zebu_root(value->root), value->root = inc_zebu_root(subgrammar);
free_zebu_root(subgrammar);
}
d = value, g = 9;
break;
}
case 19:
{
struct zebu_command* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_command* trie = data.data[--yacc.n, --data.n];
if (trie->startline < value->startline) value->startline = trie->startline;
if (value->endline < trie->endline) value->endline = trie->endline;
if (trie->args.n){
while (value->args.n + trie->args.n > value->args.cap)
{
value->args.cap = value->args.cap << 1 ?: 1;
value->args.data = realloc(value->args.data, sizeof(*value->args.data) * value->args.cap);
}
memmove(value->args.data + trie->args.n, value->args.data, sizeof(*value->args.data) * value->args.n);
for (unsigned i = 0, n = trie->args.n; i < n; i++)
value->args.data[i] = inc_zebu_token(trie->args.data[i]);
value->args.n += trie->args.n;
}
free_zebu_command(trie);
}
{
struct zebu_token* token = data.data[--yacc.n, --data.n];
if (token->line < value->startline) value->startline = token->line;
if (value->endline < token->line) value->endline = token->line;
if (value->args.n == value->args.cap)
{
value->args.cap = value->args.cap << 1 ?: 1;
value->args.data = realloc(value->args.data, sizeof(*value->args.data) * value->args.cap);
}
memmove(value->args.data + 1, value->args.data, sizeof(*value->args.data) * value->args.n);
value->args.data[0] = inc_zebu_token(token), value->args.n++;
free_zebu_token(token);
}
d = value, g = 8;
break;
}
case 16:
{
struct zebu_command* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_token* token = data.data[--yacc.n, --data.n];
if (token->line < value->startline) value->startline = token->line;
if (value->endline < token->line) value->endline = token->line;
free_zebu_token(token);
}
d = value, g = 8;
break;
}
case 15:
{
struct zebu_commands* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_command* subgrammar = data.data[--yacc.n, --data.n];
if (subgrammar->startline < value->startline) value->startline = subgrammar->startline;
if (value->endline < subgrammar->endline) value->endline = subgrammar->endline;
if (value->commands.n == value->commands.cap)
{
value->commands.cap = value->commands.cap << 1 ?: 1;
value->commands.data = realloc(value->commands.data, sizeof(*value->commands.data) * value->commands.cap);
}
memmove(value->commands.data + 1, value->commands.data, sizeof(*value->commands.data) * value->commands.n);
value->commands.data[0] = inc_zebu_command(subgrammar), value->commands.n++;
free_zebu_command(subgrammar);
}
d = value, g = 7;
break;
}
case 18:
{
struct zebu_commands* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_commands* trie = data.data[--yacc.n, --data.n];
if (trie->startline < value->startline) value->startline = trie->startline;
if (value->endline < trie->endline) value->endline = trie->endline;
if (trie->commands.n)
{
while (value->commands.n + trie->commands.n > value->commands.cap)
{
value->commands.cap = value->commands.cap << 1 ?: 1;
value->commands.data = realloc(value->commands.data, sizeof(*value->commands.data) * value->commands.cap);
}
memmove(value->commands.data + trie->commands.n, value->commands.data, sizeof(*value->commands.data) * value->commands.n);
for (unsigned i = 0, n = trie->commands.n; i < n; i++)
value->commands.data[i] = inc_zebu_command(trie->commands.data[i]);
value->commands.n += trie->commands.n;
}
free_zebu_commands(trie);
}
{
struct zebu_command* subgrammar = data.data[--yacc.n, --data.n];
if (subgrammar->startline < value->startline) value->startline = subgrammar->startline;
if (value->endline < subgrammar->endline) value->endline = subgrammar->endline;
if (value->commands.n == value->commands.cap)
{
value->commands.cap = value->commands.cap << 1 ?: 1;
value->commands.data = realloc(value->commands.data, sizeof(*value->commands.data) * value->commands.cap);
}
memmove(value->commands.data + 1, value->commands.data, sizeof(*value->commands.data) * value->commands.n);
value->commands.data[0] = inc_zebu_command(subgrammar), value->commands.n++;
free_zebu_command(subgrammar);
}
d = value, g = 7;
break;
}
case 11:
{
struct zebu_recipe* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_recipe* trie = data.data[--yacc.n, --data.n];
if (trie->startline < value->startline) value->startline = trie->startline;
if (value->endline < trie->endline) value->endline = trie->endline;
if (trie->commands) { free_zebu_commands(value->commands); value->commands = inc_zebu_commands(trie->commands); }
if (trie->depenencies.n){
while (value->depenencies.n + trie->depenencies.n > value->depenencies.cap)
{
value->depenencies.cap = value->depenencies.cap << 1 ?: 1;
value->depenencies.data = realloc(value->depenencies.data, sizeof(*value->depenencies.data) * value->depenencies.cap);
}
memmove(value->depenencies.data + trie->depenencies.n, value->depenencies.data, sizeof(*value->depenencies.data) * value->depenencies.n);
for (unsigned i = 0, n = trie->depenencies.n; i < n; i++)
value->depenencies.data[i] = inc_zebu_token(trie->depenencies.data[i]);
value->depenencies.n += trie->depenencies.n;
}
if (trie->target) { free_zebu_token(value->target); value->target = inc_zebu_token(trie->target); }
free_zebu_recipe(trie);
}
{
struct zebu_token* token = data.data[--yacc.n, --data.n];
if (token->line < value->startline) value->startline = token->line;
if (value->endline < token->line) value->endline = token->line;
if (value->depenencies.n == value->depenencies.cap)
{
value->depenencies.cap = value->depenencies.cap << 1 ?: 1;
value->depenencies.data = realloc(value->depenencies.data, sizeof(*value->depenencies.data) * value->depenencies.cap);
}
memmove(value->depenencies.data + 1, value->depenencies.data, sizeof(*value->depenencies.data) * value->depenencies.n);
value->depenencies.data[0] = inc_zebu_token(token), value->depenencies.n++;
free_zebu_token(token);
}
d = value, g = 4;
break;
}
case 7:
{
struct zebu_recipe* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_token* token = data.data[--yacc.n, --data.n];
if (token->line < value->startline) value->startline = token->line;
if (value->endline < token->line) value->endline = token->line;
free_zebu_token(token);
}
d = value, g = 4;
break;
}
case 13:
{
struct zebu_recipe* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_commands* subgrammar = data.data[--yacc.n, --data.n];
if (subgrammar->startline < value->startline) value->startline = subgrammar->startline;
if (value->endline < subgrammar->endline) value->endline = subgrammar->endline;
free_zebu_commands(value->commands), value->commands = inc_zebu_commands(subgrammar);
free_zebu_commands(subgrammar);
}
{
struct zebu_token* token = data.data[--yacc.n, --data.n];
if (token->line < value->startline) value->startline = token->line;
if (value->endline < token->line) value->endline = token->line;
free_zebu_token(token);
}
d = value, g = 4;
break;
}
case 4:
{
struct zebu_root* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_token* token = data.data[--yacc.n, --data.n];
if (token->line < value->startline) value->startline = token->line;
if (value->endline < token->line) value->endline = token->line;
free_zebu_token(token);
}
d = value, g = 3;
break;
}
case 9:
{
struct zebu_root* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_root* trie = data.data[--yacc.n, --data.n];
if (trie->startline < value->startline) value->startline = trie->startline;
if (value->endline < trie->endline) value->endline = trie->endline;
if (trie->recipes.n)
{
while (value->recipes.n + trie->recipes.n > value->recipes.cap)
{
value->recipes.cap = value->recipes.cap << 1 ?: 1;
value->recipes.data = realloc(value->recipes.data, sizeof(*value->recipes.data) * value->recipes.cap);
}
memmove(value->recipes.data + trie->recipes.n, value->recipes.data, sizeof(*value->recipes.data) * value->recipes.n);
for (unsigned i = 0, n = trie->recipes.n; i < n; i++)
value->recipes.data[i] = inc_zebu_recipe(trie->recipes.data[i]);
value->recipes.n += trie->recipes.n;
}
free_zebu_root(trie);
}
{
struct zebu_token* token = data.data[--yacc.n, --data.n];
if (token->line < value->startline) value->startline = token->line;
if (value->endline < token->line) value->endline = token->line;
free_zebu_token(token);
}
d = value, g = 3;
break;
}
case 6:
{
struct zebu_root* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_recipe* subgrammar = data.data[--yacc.n, --data.n];
if (subgrammar->startline < value->startline) value->startline = subgrammar->startline;
if (value->endline < subgrammar->endline) value->endline = subgrammar->endline;
if (value->recipes.n == value->recipes.cap)
{
value->recipes.cap = value->recipes.cap << 1 ?: 1;
value->recipes.data = realloc(value->recipes.data, sizeof(*value->recipes.data) * value->recipes.cap);
}
memmove(value->recipes.data + 1, value->recipes.data, sizeof(*value->recipes.data) * value->recipes.n);
value->recipes.data[0] = inc_zebu_recipe(subgrammar), value->recipes.n++;
free_zebu_recipe(subgrammar);
}
d = value, g = 3;
break;
}
case 10:
{
struct zebu_root* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_root* trie = data.data[--yacc.n, --data.n];
if (trie->startline < value->startline) value->startline = trie->startline;
if (value->endline < trie->endline) value->endline = trie->endline;
if (trie->recipes.n)
{
while (value->recipes.n + trie->recipes.n > value->recipes.cap)
{
value->recipes.cap = value->recipes.cap << 1 ?: 1;
value->recipes.data = realloc(value->recipes.data, sizeof(*value->recipes.data) * value->recipes.cap);
}
memmove(value->recipes.data + trie->recipes.n, value->recipes.data, sizeof(*value->recipes.data) * value->recipes.n);
for (unsigned i = 0, n = trie->recipes.n; i < n; i++)
value->recipes.data[i] = inc_zebu_recipe(trie->recipes.data[i]);
value->recipes.n += trie->recipes.n;
}
free_zebu_root(trie);
}
{
struct zebu_recipe* subgrammar = data.data[--yacc.n, --data.n];
if (subgrammar->startline < value->startline) value->startline = subgrammar->startline;
if (value->endline < subgrammar->endline) value->endline = subgrammar->endline;
if (value->recipes.n == value->recipes.cap)
{
value->recipes.cap = value->recipes.cap << 1 ?: 1;
value->recipes.data = realloc(value->recipes.data, sizeof(*value->recipes.data) * value->recipes.cap);
}
memmove(value->recipes.data + 1, value->recipes.data, sizeof(*value->recipes.data) * value->recipes.n);
value->recipes.data[0] = inc_zebu_recipe(subgrammar), value->recipes.n++;
free_zebu_recipe(subgrammar);
}
d = value, g = 3;
break;
}
case 17:
{
struct zebu_command* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_command* trie = data.data[--yacc.n, --data.n];
if (trie->startline < value->startline) value->startline = trie->startline;
if (value->endline < trie->endline) value->endline = trie->endline;
if (trie->args.n){
while (value->args.n + trie->args.n > value->args.cap)
{
value->args.cap = value->args.cap << 1 ?: 1;
value->args.data = realloc(value->args.data, sizeof(*value->args.data) * value->args.cap);
}
memmove(value->args.data + trie->args.n, value->args.data, sizeof(*value->args.data) * value->args.n);
for (unsigned i = 0, n = trie->args.n; i < n; i++)
value->args.data[i] = inc_zebu_token(trie->args.data[i]);
value->args.n += trie->args.n;
}
free_zebu_command(trie);
}
{
struct zebu_token* token = data.data[--yacc.n, --data.n];
if (token->line < value->startline) value->startline = token->line;
if (value->endline < token->line) value->endline = token->line;
if (value->args.n == value->args.cap)
{
value->args.cap = value->args.cap << 1 ?: 1;
value->args.data = realloc(value->args.data, sizeof(*value->args.data) * value->args.cap);
}
memmove(value->args.data + 1, value->args.data, sizeof(*value->args.data) * value->args.n);
value->args.data[0] = inc_zebu_token(token), value->args.n++;
free_zebu_token(token);
}
{
struct zebu_token* token = data.data[--yacc.n, --data.n];
if (token->line < value->startline) value->startline = token->line;
if (value->endline < token->line) value->endline = token->line;
free_zebu_token(token);
}
d = value, g = 5;
break;
}
case 12:
{
struct zebu_commands* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_command* subgrammar = data.data[--yacc.n, --data.n];
if (subgrammar->startline < value->startline) value->startline = subgrammar->startline;
if (value->endline < subgrammar->endline) value->endline = subgrammar->endline;
if (value->commands.n == value->commands.cap)
{
value->commands.cap = value->commands.cap << 1 ?: 1;
value->commands.data = realloc(value->commands.data, sizeof(*value->commands.data) * value->commands.cap);
}
memmove(value->commands.data + 1, value->commands.data, sizeof(*value->commands.data) * value->commands.n);
value->commands.data[0] = inc_zebu_command(subgrammar), value->commands.n++;
free_zebu_command(subgrammar);
}
d = value, g = 6;
break;
}
case 14:
{
struct zebu_commands* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_commands* trie = data.data[--yacc.n, --data.n];
if (trie->startline < value->startline) value->startline = trie->startline;
if (value->endline < trie->endline) value->endline = trie->endline;
if (trie->commands.n)
{
while (value->commands.n + trie->commands.n > value->commands.cap)
{
value->commands.cap = value->commands.cap << 1 ?: 1;
value->commands.data = realloc(value->commands.data, sizeof(*value->commands.data) * value->commands.cap);
}
memmove(value->commands.data + trie->commands.n, value->commands.data, sizeof(*value->commands.data) * value->commands.n);
for (unsigned i = 0, n = trie->commands.n; i < n; i++)
value->commands.data[i] = inc_zebu_command(trie->commands.data[i]);
value->commands.n += trie->commands.n;
}
free_zebu_commands(trie);
}
{
struct zebu_command* subgrammar = data.data[--yacc.n, --data.n];
if (subgrammar->startline < value->startline) value->startline = subgrammar->startline;
if (value->endline < subgrammar->endline) value->endline = subgrammar->endline;
if (value->commands.n == value->commands.cap)
{
value->commands.cap = value->commands.cap << 1 ?: 1;
value->commands.data = realloc(value->commands.data, sizeof(*value->commands.data) * value->commands.cap);
}
memmove(value->commands.data + 1, value->commands.data, sizeof(*value->commands.data) * value->commands.n);
value->commands.data[0] = inc_zebu_command(subgrammar), value->commands.n++;
free_zebu_command(subgrammar);
}
d = value, g = 6;
break;
}
case 8:
{
struct zebu_recipe* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_recipe* trie = data.data[--yacc.n, --data.n];
if (trie->startline < value->startline) value->startline = trie->startline;
if (value->endline < trie->endline) value->endline = trie->endline;
if (trie->commands) { free_zebu_commands(value->commands); value->commands = inc_zebu_commands(trie->commands); }
if (trie->depenencies.n){
while (value->depenencies.n + trie->depenencies.n > value->depenencies.cap)
{
value->depenencies.cap = value->depenencies.cap << 1 ?: 1;
value->depenencies.data = realloc(value->depenencies.data, sizeof(*value->depenencies.data) * value->depenencies.cap);
}
memmove(value->depenencies.data + trie->depenencies.n, value->depenencies.data, sizeof(*value->depenencies.data) * value->depenencies.n);
for (unsigned i = 0, n = trie->depenencies.n; i < n; i++)
value->depenencies.data[i] = inc_zebu_token(trie->depenencies.data[i]);
value->depenencies.n += trie->depenencies.n;
}
if (trie->target) { free_zebu_token(value->target); value->target = inc_zebu_token(trie->target); }
free_zebu_recipe(trie);
}
{
struct zebu_token* token = data.data[--yacc.n, --data.n];
if (token->line < value->startline) value->startline = token->line;
if (value->endline < token->line) value->endline = token->line;
free_zebu_token(token);
}
{
struct zebu_token* token = data.data[--yacc.n, --data.n];
if (token->line < value->startline) value->startline = token->line;
if (value->endline < token->line) value->endline = token->line;
free_zebu_token(value->target), value->target = inc_zebu_token(token);
free_zebu_token(token);
}
d = value, g = 1;
break;
}
case 3:
{
struct zebu_root* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_root* trie = data.data[--yacc.n, --data.n];
if (trie->startline < value->startline) value->startline = trie->startline;
if (value->endline < trie->endline) value->endline = trie->endline;
if (trie->recipes.n)
{
while (value->recipes.n + trie->recipes.n > value->recipes.cap)
{
value->recipes.cap = value->recipes.cap << 1 ?: 1;
value->recipes.data = realloc(value->recipes.data, sizeof(*value->recipes.data) * value->recipes.cap);
}
memmove(value->recipes.data + trie->recipes.n, value->recipes.data, sizeof(*value->recipes.data) * value->recipes.n);
for (unsigned i = 0, n = trie->recipes.n; i < n; i++)
value->recipes.data[i] = inc_zebu_recipe(trie->recipes.data[i]);
value->recipes.n += trie->recipes.n;
}
free_zebu_root(trie);
}
{
struct zebu_token* token = data.data[--yacc.n, --data.n];
if (token->line < value->startline) value->startline = token->line;
if (value->endline < token->line) value->endline = token->line;
free_zebu_token(token);
}
d = value, g = 2;
break;
}
case 1:
{
struct zebu_root* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_recipe* subgrammar = data.data[--yacc.n, --data.n];
if (subgrammar->startline < value->startline) value->startline = subgrammar->startline;
if (value->endline < subgrammar->endline) value->endline = subgrammar->endline;
if (value->recipes.n == value->recipes.cap)
{
value->recipes.cap = value->recipes.cap << 1 ?: 1;
value->recipes.data = realloc(value->recipes.data, sizeof(*value->recipes.data) * value->recipes.cap);
}
memmove(value->recipes.data + 1, value->recipes.data, sizeof(*value->recipes.data) * value->recipes.n);
value->recipes.data[0] = inc_zebu_recipe(subgrammar), value->recipes.n++;
free_zebu_recipe(subgrammar);
}
d = value, g = 2;
break;
}
case 5:
{
struct zebu_root* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
value->refcount = 1;
value->startline = -1;
value->endline = 0;
{
struct zebu_root* trie = data.data[--yacc.n, --data.n];
if (trie->startline < value->startline) value->startline = trie->startline;
if (value->endline < trie->endline) value->endline = trie->endline;
if (trie->recipes.n)
{
while (value->recipes.n + trie->recipes.n > value->recipes.cap)
{
value->recipes.cap = value->recipes.cap << 1 ?: 1;
value->recipes.data = realloc(value->recipes.data, sizeof(*value->recipes.data) * value->recipes.cap);
}
memmove(value->recipes.data + trie->recipes.n, value->recipes.data, sizeof(*value->recipes.data) * value->recipes.n);
for (unsigned i = 0, n = trie->recipes.n; i < n; i++)
value->recipes.data[i] = inc_zebu_recipe(trie->recipes.data[i]);
value->recipes.n += trie->recipes.n;
}
free_zebu_root(trie);
}
{
struct zebu_recipe* subgrammar = data.data[--yacc.n, --data.n];
if (subgrammar->startline < value->startline) value->startline = subgrammar->startline;
if (value->endline < subgrammar->endline) value->endline = subgrammar->endline;
if (value->recipes.n == value->recipes.cap)
{
value->recipes.cap = value->recipes.cap << 1 ?: 1;
value->recipes.data = realloc(value->recipes.data, sizeof(*value->recipes.data) * value->recipes.cap);
}
memmove(value->recipes.data + 1, value->recipes.data, sizeof(*value->recipes.data) * value->recipes.n);
value->recipes.data[0] = inc_zebu_recipe(subgrammar), value->recipes.n++;
free_zebu_recipe(subgrammar);
}
d = value, g = 2;
break;
}
}
			
			if (g == 9)
			{
				free_zebu_token(td);
				yacc.n = 0, root = d;
			}
			else
			{
				y = yacc.data[yacc.n - 1];
				
				#ifdef ZEBU_DEBUG
				ddprintf("y = %u\n", y);
				#endif
				
				assert(y < N(zebu_gotos) && g < N(*zebu_gotos));
				
				s = zebu_gotos[y][g];
				
				#ifdef ZEBU_DEBUG
				ddprintf("s = %u\n", s);
				#endif
				
				y = s, push_state(y), push_data(d);
			}
		}
		else
		{
			struct zebu_token* token = td;
			
			fprintf(stderr, "zebu: unexpected token '%.*s'!\n", token->len, token->data);
			
			exit(1);
		}
	}
	
	#ifdef ZEBU_DEBUG
	print_zebu_$start(NULL, p_root, "start", root);
	#endif
	
	free(yacc.data);
	free(data.data);
	free(lexer.data);
	
	return root;
}

















