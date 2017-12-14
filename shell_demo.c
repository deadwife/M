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
#define CLS system("clear");
#define BUFSIZE 8096

int main()
{
     Tree * Tree;
     char cur_str[BUFSIZE];
     char * demolished_args[BUFSIZE];
Begin:

     write(1,">: ", 3);
     Tree = NULL;
     //
     Tree = exp0(cur_str); //Grow a Tree from a Crop
     //
     executor2000(Tree, demolished_args); //Do stuff
     //
     lumberjack3000(Tree); //Free a tree
     //
goto Begin;
     return 0;
}
