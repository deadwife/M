#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "head/my_funcs.h"

int main(int argc, char * argv[])
{
     int fd, l_count, w_count, s_count, reader, flag;
     char * filename = argv[1];
     char c;

     l_count = 0;
     w_count = 0;
     s_count = 0;
     flag = 0;

     fd = open(filename, O_RDONLY);
     if (fd == -1)
          error("file not found");
     while ((reader = read(fd, &c, 1)) > 0)
     {
          if (c == ' ')
          {
               if (flag)
                    w_count++;
          }
          else
               if (c == '\n')
               {
                    s_count++;
                    flag = 0;
               }
               else
               {
                    if (!flag)
                         w_count++;
                    flag = 1;
               }
           l_count++;
     }
     printf("%d   ", l_count);
     if (l_count != 0)
          printf("%d    ", w_count);
     else
          printf("0    ");
     printf("%d\n", s_count);
     return 0;
}
