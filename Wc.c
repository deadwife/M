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
     write(1, &l_count, 1);
     write(1, "    ", 4);
     if (l_count != 0)
          write(1, &w_count, 1);
     else
          write(1, "0", 1);
     write(1, "    ", 4);
     write(1, &s_count, 1);
     return 0;
}