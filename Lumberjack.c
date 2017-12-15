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

void lumberjack3000(Tree * Crop)
{
     if (Crop->left != NULL)
          lumberjack3000(Crop->left);
     if (Crop->right != NULL)
          lumberjack3000(Crop->right);
     if(Crop->args != NULL)
          free(Crop->args);
     free(Crop);
}