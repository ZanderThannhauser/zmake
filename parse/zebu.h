
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

struct zebu_additive_expression
{
struct zebu_token* add;
struct zebu_multiplicative_expression* inner;
struct zebu_additive_expression* left;
struct zebu_multiplicative_expression* right;
struct zebu_token* sub;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_and_expression
{
struct zebu_equality_expression* inner;
struct zebu_and_expression* left;
struct zebu_equality_expression* right;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_argument
{
struct zebu_expression* expression;
struct zebu_token* string;
struct zebu_token* text;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_assignment
{
struct zebu_token* addeq;
struct zebu_token* andeq;
struct zebu_token* diveq;
struct zebu_token* eq;
struct zebu_expression* expression;
struct zebu_token* ioreq;
struct zebu_token* lsheq;
struct zebu_token* modeq;
struct zebu_token* muleq;
struct zebu_token* rsheq;
struct zebu_token* subeq;
struct zebu_token* variable;
struct zebu_token* xoreq;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_command
{
struct zebu_argument* redirect_in;
struct zebu_argument* redirect_out;
struct {
struct zebu_simple_command** data;
unsigned n, cap;
} simples;
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

struct zebu_conditional
{
struct zebu_expression* conditional;
struct {
struct zebu_statement** data;
unsigned n, cap;
} falsecase;
struct {
struct zebu_statement** data;
unsigned n, cap;
} truecase;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_conditional_expression
{
struct zebu_conditional_expression* falsecase;
struct zebu_logical_or_expression* inner;
struct zebu_expression* truecase;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_equality_expression
{
struct zebu_token* eq;
struct zebu_relational_expression* inner;
struct zebu_equality_expression* left;
struct zebu_token* nq;
struct zebu_relational_expression* right;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_exclusive_or_expression
{
struct zebu_and_expression* inner;
struct zebu_exclusive_or_expression* left;
struct zebu_and_expression* right;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_expression
{
struct zebu_conditional_expression* inner;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_include
{
struct zebu_argument* argument;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_inclusive_or_expression
{
struct zebu_exclusive_or_expression* inner;
struct zebu_inclusive_or_expression* left;
struct zebu_exclusive_or_expression* right;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_iterative
{
struct {
struct zebu_statement** data;
unsigned n, cap;
} body;
struct zebu_expression* list;
struct zebu_token* variable;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_logical_and_expression
{
struct zebu_inclusive_or_expression* inner;
struct zebu_logical_and_expression* left;
struct zebu_inclusive_or_expression* right;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_logical_or_expression
{
struct zebu_logical_and_expression* inner;
struct zebu_logical_or_expression* left;
struct zebu_logical_and_expression* right;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_multiplicative_expression
{
struct zebu_token* div;
struct zebu_prefix_expression* inner;
struct zebu_multiplicative_expression* left;
struct zebu_token* mul;
struct zebu_prefix_expression* right;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_postfix_expression
{
struct zebu_primary_expression* inner;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_prefix_expression
{
struct zebu_postfix_expression* inner;
struct zebu_token* neg;
struct zebu_token* pos;
struct zebu_prefix_expression* sub;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_primary_expression
{
struct {
struct zebu_expression** data;
unsigned n, cap;
} elements;
struct zebu_expression* inner;
struct zebu_token* integer;
struct zebu_token* list;
struct zebu_token* string;
struct zebu_token* variable;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_print
{
struct zebu_expression* expression;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_recipe
{
struct zebu_commands* commands;
struct {
struct zebu_argument** data;
unsigned n, cap;
} dependencies;
struct zebu_argument* target;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_relational_expression
{
struct zebu_token* gt;
struct zebu_token* gte;
struct zebu_shift_expression* inner;
struct zebu_relational_expression* left;
struct zebu_token* lt;
struct zebu_token* lte;
struct zebu_shift_expression* right;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_root
{
struct {
struct zebu_statement** data;
unsigned n, cap;
} statements;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_shift_expression
{
struct zebu_additive_expression* inner;
struct zebu_shift_expression* left;
struct zebu_token* leftshift;
struct zebu_additive_expression* right;
struct zebu_token* rightshift;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_simple_command
{
struct {
struct zebu_argument** data;
unsigned n, cap;
} args;
unsigned refcount;
unsigned startline, endline;
};

struct zebu_statement
{
struct zebu_assignment* assignment;
struct zebu_conditional* conditional;
struct zebu_include* include;
struct zebu_iterative* iterative;
struct zebu_print* print;
struct zebu_recipe* recipe;
unsigned refcount;
unsigned startline, endline;
};



extern struct zebu_token* inc_zebu_token(struct zebu_token* token);
extern struct zebu_$start* inc_zebu_$start(struct zebu_$start* ptree);
extern struct zebu_additive_expression* inc_zebu_additive_expression(struct zebu_additive_expression* ptree);
extern struct zebu_and_expression* inc_zebu_and_expression(struct zebu_and_expression* ptree);
extern struct zebu_argument* inc_zebu_argument(struct zebu_argument* ptree);
extern struct zebu_assignment* inc_zebu_assignment(struct zebu_assignment* ptree);
extern struct zebu_command* inc_zebu_command(struct zebu_command* ptree);
extern struct zebu_commands* inc_zebu_commands(struct zebu_commands* ptree);
extern struct zebu_conditional* inc_zebu_conditional(struct zebu_conditional* ptree);
extern struct zebu_conditional_expression* inc_zebu_conditional_expression(struct zebu_conditional_expression* ptree);
extern struct zebu_equality_expression* inc_zebu_equality_expression(struct zebu_equality_expression* ptree);
extern struct zebu_exclusive_or_expression* inc_zebu_exclusive_or_expression(struct zebu_exclusive_or_expression* ptree);
extern struct zebu_expression* inc_zebu_expression(struct zebu_expression* ptree);
extern struct zebu_include* inc_zebu_include(struct zebu_include* ptree);
extern struct zebu_inclusive_or_expression* inc_zebu_inclusive_or_expression(struct zebu_inclusive_or_expression* ptree);
extern struct zebu_iterative* inc_zebu_iterative(struct zebu_iterative* ptree);
extern struct zebu_logical_and_expression* inc_zebu_logical_and_expression(struct zebu_logical_and_expression* ptree);
extern struct zebu_logical_or_expression* inc_zebu_logical_or_expression(struct zebu_logical_or_expression* ptree);
extern struct zebu_multiplicative_expression* inc_zebu_multiplicative_expression(struct zebu_multiplicative_expression* ptree);
extern struct zebu_postfix_expression* inc_zebu_postfix_expression(struct zebu_postfix_expression* ptree);
extern struct zebu_prefix_expression* inc_zebu_prefix_expression(struct zebu_prefix_expression* ptree);
extern struct zebu_primary_expression* inc_zebu_primary_expression(struct zebu_primary_expression* ptree);
extern struct zebu_print* inc_zebu_print(struct zebu_print* ptree);
extern struct zebu_recipe* inc_zebu_recipe(struct zebu_recipe* ptree);
extern struct zebu_relational_expression* inc_zebu_relational_expression(struct zebu_relational_expression* ptree);
extern struct zebu_root* inc_zebu_root(struct zebu_root* ptree);
extern struct zebu_shift_expression* inc_zebu_shift_expression(struct zebu_shift_expression* ptree);
extern struct zebu_simple_command* inc_zebu_simple_command(struct zebu_simple_command* ptree);
extern struct zebu_statement* inc_zebu_statement(struct zebu_statement* ptree);


extern void free_zebu_token(struct zebu_token* token);
extern void free_zebu_$start(struct zebu_$start* ptree);

extern void free_zebu_additive_expression(struct zebu_additive_expression* ptree);

extern void free_zebu_and_expression(struct zebu_and_expression* ptree);

extern void free_zebu_argument(struct zebu_argument* ptree);

extern void free_zebu_assignment(struct zebu_assignment* ptree);

extern void free_zebu_command(struct zebu_command* ptree);

extern void free_zebu_commands(struct zebu_commands* ptree);

extern void free_zebu_conditional(struct zebu_conditional* ptree);

extern void free_zebu_conditional_expression(struct zebu_conditional_expression* ptree);

extern void free_zebu_equality_expression(struct zebu_equality_expression* ptree);

extern void free_zebu_exclusive_or_expression(struct zebu_exclusive_or_expression* ptree);

extern void free_zebu_expression(struct zebu_expression* ptree);

extern void free_zebu_include(struct zebu_include* ptree);

extern void free_zebu_inclusive_or_expression(struct zebu_inclusive_or_expression* ptree);

extern void free_zebu_iterative(struct zebu_iterative* ptree);

extern void free_zebu_logical_and_expression(struct zebu_logical_and_expression* ptree);

extern void free_zebu_logical_or_expression(struct zebu_logical_or_expression* ptree);

extern void free_zebu_multiplicative_expression(struct zebu_multiplicative_expression* ptree);

extern void free_zebu_postfix_expression(struct zebu_postfix_expression* ptree);

extern void free_zebu_prefix_expression(struct zebu_prefix_expression* ptree);

extern void free_zebu_primary_expression(struct zebu_primary_expression* ptree);

extern void free_zebu_print(struct zebu_print* ptree);

extern void free_zebu_recipe(struct zebu_recipe* ptree);

extern void free_zebu_relational_expression(struct zebu_relational_expression* ptree);

extern void free_zebu_root(struct zebu_root* ptree);

extern void free_zebu_shift_expression(struct zebu_shift_expression* ptree);

extern void free_zebu_simple_command(struct zebu_simple_command* ptree);

extern void free_zebu_statement(struct zebu_statement* ptree);



struct zebu_$start* zebu_parse(FILE* stream);
