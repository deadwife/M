#include <fcntl.h>
#include <unistd.h>
#include "head/my_funcs.h"
#define BUFSIZE 8096

int main(int argc, char * argv[])
{
     char * filename = argv[1];
     char * filename1 = argv[2];
     int fd, fd1;
     char  buf[BUFSIZE];
     int count;

     fd = open(filename, O_RDONLY);
     if (fd == -1)
          error("file not found");
     fd1 = open(filename1, O_WRONLY | O_CREAT);
     while ((count = read(fd, buf, BUFSIZE)) > 0)
          write(fd1, buf, count);
     close(fd);
     close(fd1);
     return 0;
}