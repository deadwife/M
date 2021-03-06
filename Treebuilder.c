#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "head/my_funcs.h"
#include "head/my_tps.h"
#define S sleep(999);
#define BUFSIZE 512

Tree * exp0(Lex * code, char * cur_str)
{
     Tree * Crop = NULL,* Crop0 = NULL;
     Crop = expr(code, cur_str);
     if (*code == _zero)
          *code = nextlex(cur_str);
     while (*code == _background)
     {
          Crop0 = (Tree *) calloc (1, sizeof(Tree));
          Crop0->code = *code;
          Crop0->args = NULL;
          Crop0->left = Crop;
          Crop0->right = expr(code, cur_str);
          Crop = Crop0;
          if (*code == _zero)
               *code = nextlex(cur_str);
     }
     if (*code != _eoln)
     {
          error("string error - almost created a tree - sleeping...\n");
          S
     }
     return Crop;
}


/////////////////////////////////////////////////////////////////////


Tree * expr(Lex * code, char * cur_str)
{
     Tree * Crop = NULL,* Crop0 = NULL;
     Crop = item(code, cur_str);
     if (*code == _zero)
          *code = nextlex(cur_str);
     while ((*code == _and) || (*code == _or))
     {
          Crop0 = (Tree *) calloc (1, sizeof(Tree));
          Crop0->code = *code;
          Crop0->args = NULL;
          Crop0->left = Crop;
          Crop0->right = item(code, cur_str);
          Crop = Crop0;
          if (*code == _zero)
               *code = nextlex(cur_str);
     }
     return Crop;
}


/////////////////////////////////////////////////////////////////////


Tree * item(Lex * code, char * cur_str)
{
     Tree * Crop = NULL,* Crop0 = NULL;
     Crop = head(code, cur_str);
     if (*code == _zero)
          *code = nextlex(cur_str);
     while (*code == _pipe)
     {
          Crop0 = (Tree *) calloc (1, sizeof(Tree));
          Crop0->code = *code;
          Crop0->args = NULL;
          Crop0->left = Crop;
          Crop0->right = head(code, cur_str);
          Crop = Crop0;
          if (*code == _zero)
               *code = nextlex(cur_str);
     }
     return Crop;
}


/////////////////////////////////////////////////////////////////////


Tree * head(Lex * code, char * cur_str)
{
     Tree * Crop = NULL,* Crop0 = NULL;
     Crop = mult(code, cur_str);
     if (*code == _zero)
     {
          *code = nextlex(cur_str);
     }
     while ((*code == _redirectL) || (*code == _redirectR) || (*code == _redirectRR))
     {
          Crop0 = (Tree *) calloc (1, sizeof(Tree));
          Crop0->code = *code;
          Crop0->args = string_demolisherXXX(cur_str);
          Crop0->left = Crop;
          Crop0->right = mult(code, cur_str);
          Crop = Crop0;
          if (*code == _zero)
               *code = nextlex(cur_str);
     }
     return Crop;
}


/////////////////////////////////////////////////////////////////////


Tree * mult(Lex * code, char * cur_str)
{
     Tree * Crop = NULL;
     Crop = (Tree *) calloc (1, sizeof(Tree));
     Crop->left = NULL;
     Crop->right = NULL;
     if((*code = nextlex(cur_str)) == _arg)
     {
          Crop->code = *code;
          Crop->args = string_demolisherXXX(cur_str);
          *code = _zero;
     }
     return Crop;
}
