#pragma once
#define BUFSIZE1 50

typedef enum Lex {
     _zero,
     _arg,
     _and,
     _pipe,
     _background, //4
     _redirectR,
     _redirectRR,
     _redirectL,
     _or, //8
     _eoln} Lex;

typedef struct arr {
     char arg1[BUFSIZE1];
     char arg2[BUFSIZE1];
     char arg3[BUFSIZE1];
     char arg4[BUFSIZE1];
     char arg5[BUFSIZE1];
} arr;

typedef struct Tree {
     Lex code;
     arr * args;
     struct Tree * left;
     struct Tree * right;
} Tree;


