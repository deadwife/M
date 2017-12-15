#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "head/my_funcs.h"
#include "head/my_tps.h"
#define CLS system("clear");
#define BUFSIZE 512

// UTILITIES

void error(const char * str)
{
     write(1, str, 100);
}


/////////////////////////////////////////////////////////////////////


void skip(int * c)
{
     do
     {
          *c = getchar();
     }
     while (*c == ' ');
}


///////////////////////////////////////////////////////////////////


Lex nextlex(char * cur_str)
{
     int c;
     skip(&c);
     cur_str[0] = '\0';
     if ((c == '\n'))
          return _eoln;
//printf("in nextlex c = %c\n", c);
     switch (c)
     {
          case '&':
          {
               c = getchar();
               if (c == '&')
                    return _and;
               else
               {
                    ungetc(c, stdin);
                    return _background;
               }
               break;
          }
          case '|':
          {
               c = getchar();
               if (c == '|')
                    return _or;
               else
               {
                    ungetc(c, stdin);
                    return _pipe;
               }
               break;
          }
          case '>':
          {
               c = getchar();
               if (c == '>')
                    return _redirectRR;
               else
               {
                    ungetc(c, stdin);
                    return _redirectR;
               }
               break;
          }
          case '<':
          {
               return _redirectL;
               break;
          }
          default:
          {
               char buf[BUFSIZE];
               int j, i = 0;
               while(
                      (c != '&') &&
                      (c != '|') &&
                      (c != '>') &&
                      (c != '<') &&
                      (c != '\n')
                    )
               {
                    buf[i] = c;
                    c = getchar();
//printf("in nextlex c = %c\n", c);
                    i++;
               }
               ungetc(c, stdin);
//printf("in nextlex u = %c\n", u);
               for (j = 0; j < i; j++)
               {
                    cur_str[j] = buf[j];
               }
               cur_str[j] = '\0';
               return _arg;
               break;
          }
     }
}
/////////////////////////////////////////////////////////////////////


arr * string_demolisherXXX(char * args)
{
     char c;
     int i = 0, j = 0, k = 0;
     arr * p = (arr *) calloc (1, sizeof(arr));
     p->arg1[0] = '\0';
     p->arg2[0] = '\0';
     p->arg3[0] = '\0';
     p->arg4[0] = '\0';
     p->arg5[0] = '\0';
     do
     {
          c = args[i];
          if (c != '\n')
               (p->arg1)[k] = c;
          k++;
          i++;
     }
     while ((c != ' ') && (c != '\n') && (c != '\0'));
     (p->arg1)[k - 1] = '\0';
     k = 0;
     j++;

if (c == '\0')
     return p;

     do
     {
          c = args[i];
          if (c != '\n')
               (p->arg2)[k] = c;
          i++;
          k++;
     }
     while ((c != ' ') && (c != '\n') && (c != '\0'));
     (p->arg2)[k - 1] = '\0';
     j++;
     k = 0;


if (c == '\0')
     return p;

     do
     {
          c = args[i];
          if (c != '\n')
               (p->arg3)[k] = c;
          i++;
          k++;
     }
     while ((c != ' ') && (c != '\n') && (c != '\0'));
     (p->arg3)[k - 1] = '\0';
     k = 0;
     j++;

if (c == '\0')
     return p;

     do
     {
          c = args[i];
          if (c != '\n')
               (p->arg4)[k] = c;
          i++;
          k++;
     }
     while ((c != ' ') && (c != '\n') && (c != '\0'));
     (p->arg4)[k - 1] = '\0';
     j++;
     k = 0;

if (c == '\0')
     return p;

     do
     {
          c = args[i];
          if (c != '\n')
               (p->arg5)[k] = c;
          i++;
          k++;
     }
     while ((c != ' ') && (c != '\n') && (c != '\0'));
     (p->arg5)[k - 1] = '\0';
     j++;
     k = 0;

     return p;
}


/////////////////////////////////////////////////////////////////////


void printTree(Tree * Crop)
{
     puts("///////////////////////////////////////");
     if (Crop->args != NULL)
          printf("code: %d\nargs:\n1: %s\n2: %s\n", Crop->code,Crop->args->arg1,Crop->args->arg2);
     else
          printf("code: %d\nl:\n %p\nr:\n %p\n", Crop->code,Crop->left,Crop->right);
}


/////////////////////////////////////////////////////////////////////


void argformer(char ** argv, arr * p)
{
     int i = 0;
     if (p->arg1[0] != '\0')
     {
          argv[i] = p->arg1;
          i++;
     }
     if (p->arg2[0] != '\0')
     {
          argv[i] = p->arg2;
          i++;
     }
     if (p->arg3[0] != '\0')
     {
          argv[i] = p->arg3;
          i++;
     }
     if (p->arg4[0] != '\0')
     {
          argv[i] = p->arg4;
          i++;
     }
     if (p->arg5[0] != '\0')
     {
          argv[i] = p->arg5;
          i++;
     }
     argv[i] = NULL;
}


/////////////////////////////////////////////////////////////////////


void Printer(Tree * Crop)
{
     if (Crop->left != NULL)
          Printer(Crop->left);
     if (Crop->right != NULL)
          Printer(Crop->right);
     printTree(Crop);
}


/////////////////////////////////////////////////////////////////////


void Rootplacer(arr * Root)
{
     if (Root->arg1[0] == '\0')
     {
          Root->arg1[0] = 't';
          Root->arg1[1] = '\0';
          return;
     }
     if (Root->arg2[0] == '\0')
     {
          Root->arg2[0] = 't';
          Root->arg2[1] = '\0';
          return;
     }
     if (Root->arg3[0] == '\0')
     {
          Root->arg3[0] = 't';
          Root->arg3[1] = '\0';
          return;
     }
     if (Root->arg4[0] == '\0')
     {
          Root->arg4[0] = 't';
          Root->arg4[1] = '\0';
          return;
     }
     Root->arg5[0] = 't';
     Root->arg5[1] = '\0';
     return;
}