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
#define BUFSIZE 8096

Tree * exp0()
{
     char cur_str[BUFSIZE];
     Lex code;
     Tree * Crop = NULL,* Crop0 = NULL;
     Crop = expr();
     while ((code = nextlex(cur_str)) == _background)
     {
          Crop0 = (Tree *) calloc (1, sizeof(Tree));
          Crop0->code = code;
          Crop0->args = NULL;
          Crop0->left = Crop;
          Crop0->right = expr();
          Crop = Crop0;
     }
     if (cur_str[0] != '\0')
     {
          error("string error - almost created a tree - sleeping...\n");
          S
     }
     return Crop;
}


/////////////////////////////////////////////////////////////////////


Tree * expr()
{
     char cur_str[BUFSIZE];
     Lex code;
     Tree * Crop = NULL,* Crop0 = NULL;
     Crop = item();
     while (((code = nextlex(cur_str)) == _and) || (code == _or))
     {
          Crop0 = (Tree *) calloc (1, sizeof(Tree));
          Crop0->code = code;
          Crop0->args = NULL;
          Crop0->left = Crop;
          Crop0->right = item();
          Crop = Crop0;
     }
     return Crop;
}


/////////////////////////////////////////////////////////////////////


Tree * item()
{
     char cur_str[BUFSIZE];
     Lex code;
     Tree * Crop = NULL,* Crop0 = NULL;
     Crop = head();
     while ((code = nextlex(cur_str)) == _pipe)
     {
          Crop0 = (Tree *) calloc (1, sizeof(Tree));
          Crop0->code = code;
          Crop0->args = NULL;
          Crop0->left = Crop;
          Crop0->right = head();
          Crop = Crop0;
     }
     return Crop;
}


/////////////////////////////////////////////////////////////////////


Tree * head()
{
     char cur_str[BUFSIZE];
     Lex code;
     Tree * Crop = NULL,* Crop0 = NULL;
     Crop = mult();
     while ((code = nextlex(cur_str)) == _redirect)
     {
          Crop0 = (Tree *) calloc (1, sizeof(Tree));
          Crop0->code = code;
          if ((code = nextlex(cur_str)) == _arg)
               Crop0->args = cur_str;
          else
          {
               error("in head - no args - sleeping...\n");
               S
          }
          Crop0->left = Crop;
          Crop0->right = mult();
          Crop = Crop0;
     }
     return Crop;
}


/////////////////////////////////////////////////////////////////////


Tree * mult()
{
     char cur_str[BUFSIZE];
     Lex code;
     Tree * Crop = NULL;
     Crop = (Tree *) calloc (1, sizeof(Tree));
     Crop->left = NULL;
     Crop->right = NULL;
     if((code = nextlex(cur_str)) == _arg)
          Crop->code = _arg;
     else
     {
          error("in mult - UNKNOWN LEX - sleeping...\n");
          S
     }
     Crop->args = cur_str;
     return Crop;
}
