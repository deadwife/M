#include <fcntl.h>
#include <unistd.h>
#include "head/my_funcs.h"
#define BUFSIZE 8096


int main(int argc, char * argv[])
{
     char * filename = argv[1];
     int fd, reader;
     char c;
     fd = open(filename, O_RDONLY);
     if (fd == -1)
          error("file not found");
     while ((reader = read(fd, &c, 1)) > 0)
          write(1, &c, 1);
     return 0;
}
