
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>

struct zebu_token
{
unsigned char* data;
unsigned len, refcount;
unsigned line;
unsigned startcol, endcol;
};
struct zebu_$start
{
struct zebu_root* root;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_command
{
struct {
struct zebu_token** data;
unsigned n, cap;
} args;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_commands
{
struct {
struct zebu_command** data;
unsigned n, cap;
} commands;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_recipe
{
struct zebu_commands* commands;
struct {
struct zebu_token** data;
unsigned n, cap;
} depenencies;
struct zebu_token* target;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_root
{
struct {
struct zebu_recipe** data;
unsigned n, cap;
} recipes;
unsigned refcount;
unsigned startline, endline;
};



extern struct zebu_token* inc_zebu_token(struct zebu_token* token);
extern struct zebu_$start* inc_zebu_$start(struct zebu_$start* ptree);
extern struct zebu_command* inc_zebu_command(struct zebu_command* ptree);
extern struct zebu_commands* inc_zebu_commands(struct zebu_commands* ptree);
extern struct zebu_recipe* inc_zebu_recipe(struct zebu_recipe* ptree);
extern struct zebu_root* inc_zebu_root(struct zebu_root* ptree);


extern void free_zebu_token(struct zebu_token* token);
extern void free_zebu_$start(struct zebu_$start* ptree);

extern void free_zebu_command(struct zebu_command* ptree);

extern void free_zebu_commands(struct zebu_commands* ptree);

extern void free_zebu_recipe(struct zebu_recipe* ptree);

extern void free_zebu_root(struct zebu_root* ptree);



struct zebu_$start* zebu_parse(FILE* stream);
