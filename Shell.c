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
#define BUFSIZE 512

int main()
{
     Tree * Tree = NULL;
     char cur_str[BUFSIZE];
     Lex code;
     int fd, fd1;
Begin:
     fd = open("err", O_RDWR | O_TRUNC);
     fd1 = dup(2);
     dup2(fd ,2);
     write(1,">: ", 3);
     //
     Tree = exp0(&code, cur_str); //Grow a Tree from a Crop

     // Printer(Tree);
     // puts("///////////////////////////////////////");

     executor2000(Tree); //Do stuff
     //
     lumberjack3000(Tree); //Free a tree
     dup2(fd1 ,2);
     close(fd1);
     close(fd);
goto Begin;
     return 0;
}
