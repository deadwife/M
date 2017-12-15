#pragma once
#include "my_tps.h"

void error(const char * str);
void skip(int * c);
Lex nextlex(char * cur_str);
void getbuf(char *);
void createbuf(char **);
void resetbuf(char *);
void printTree(Tree * Crop);
void argformer(char ** argv, arr * p);
void Printer(Tree * Crop);
void Rootplacer(arr * Root);
arr * string_demolisherXXX(char * args);

Tree * exp0(Lex * code,char * cur_str);
Tree * expr(Lex * code, char * cur_str);
Tree * item(Lex * code, char * cur_str);
Tree * head(Lex * code, char * cur_str);
Tree * mult(Lex * code, char * cur_str);

int executor2000(Tree *);

void lumberjack3000(Tree *); //!!!!!!!!!!!!!!!!!!11
