#pragma once

typedef enum Lex {
     _zero,
     _arg,
     _command0,
     _and,
     _pipe,
     _background,
     _redirect,
     _or,
     _eoln} Lex;

typedef struct Tree {
     Lex code;
     char * args;
     struct Tree * left;
     struct Tree * right;
} Tree;
