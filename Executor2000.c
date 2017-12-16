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



int executor2000(Tree * Tree)
{
     int success = 1;
     switch (Tree->code)
     {
     case _background:                                                     //     &
          {
               int fd;
               setpgrp();
               fd = dup(0);
               close(0);
               if (Tree->left != NULL)
               {
                    if (fork() == 0)
                    {
                         success = executor2000(Tree->left);
                         raise(SIGKILL);
                    }
                    else
                         wait(NULL);
               }
               else
                    success = -1;
               dup2(fd, 0);
               close(fd);
               if (Tree->right != NULL)
                    success = executor2000(Tree->right);
               else
                    success = -1;
               break;
          }
     case _and:                                                            //     &&
          {
               if (Tree->left != NULL)
                    success = executor2000(Tree->left);
               else
                    return -1;
               if ((Tree->right != NULL) && success)
                    success = executor2000(Tree->right);
               else
                    return -1;
               break;
          }
     case _or:                                                             //      ||
          {
               if (Tree->left != NULL)
                    success = executor2000(Tree->left);
               else
                    return -1;
               if ((Tree->right != NULL) && (success == -1))
                    success = executor2000(Tree->right);
               else
                    return -1;
               break;
          }
     case _pipe:                                                            //      |
          {
               int fd, fd1;
               struct Tree * Root = Tree;
               fd = open("t", O_RDWR | O_TRUNC);
               fd1= dup(1);
               dup2(fd, 1);
               if (Tree->left != NULL)
                    success = executor2000(Tree->left); //left > t
               else
                    success = -1;
               dup2(fd1, 1);
               close(fd1);
               fd1 = dup(0);
               dup2(fd, 0);
               Root = Root->right;
               Rootplacer(Root->args);
               if ((Tree->right != NULL) && success)
                    success = executor2000(Tree->right); // right < t
               dup2(fd1, 0);
               close(fd1);
               close(fd);
               if(success == -1)
               {
                    error("in piped command");
                    raise(SIGKILL);
               }
               break;
          }
     case _redirectR:                                                      //      >
          {
               int fd, fd1;
               char * filename;
               if (Tree->right != NULL)
               {
                    filename = Tree->right->args->arg1;
                    fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
                    fd1 = dup(1);
                    dup2(fd, 1);
               }
               else
                    return -1;
               if (Tree->left != NULL)
                    success = executor2000(Tree->left);
               else
                    success = -1;
               dup2(fd1,1);
               close(fd);
               close(fd1);
               break;
          }
     case _redirectRR:                                                           //      >>
          {
               int fd, fd1;
               char * filename;
               if (Tree->right != NULL)
               {
                    filename = Tree->right->args->arg1;
                    fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
                    fd1 = dup(1);
                    dup2(fd, 1);
               }
               else
                    return -1;
               if (Tree->left != NULL)
                    success = executor2000(Tree->left);
               else
                    success = -1;
               dup2(fd1,1);
               close(fd);
               close(fd1);
               break;
          }
     case _redirectL:                                                              //       <
          {
               int fd, fd1;
               char * filename;
               if (Tree->right != NULL)
               {
                    filename = Tree->right->args->arg1;
                    fd = open(filename, O_RDONLY, 0666);
                    fd1 = dup(0);
                    dup2(fd, 0);
               }
               else
                    return -1;
               if (Tree->left != NULL)
                    success = executor2000(Tree->left);
               else
                    success = -1;
               dup2(fd1,0);
               close(fd);
               close(fd1);
               break;
          }
          case _arg:                                                                //      argument
          {
               char * Arguments[6];
               if (strcmp(Tree->args->arg1, "cp") == 0)
               {
                    int fd[2];
                    pipe(fd);
                    if (fork() > 0)
                    {
                         wait(NULL);
                         close(fd[1]);
                         read(fd[0], &success, 1);
                         close(fd[0]);
                         return success;
                    }
                    else
                    {
                         argformer(Arguments, Tree->args);
                         success = execv("Copy.exe", Arguments);
                         printf("command error in %s\n", Tree->args->arg1);
                         write(fd[1], &success, 1);
                         raise(SIGKILL);
                    }
               }
               else
                    if (strcmp(Tree->args->arg1, "wc") == 0)
                    {
                         int fd[2];
                         pipe(fd);
                         if (fork() > 0)
                         {
                              wait(NULL);
                              close(fd[1]);
                              read(fd[0], &success, 1);
                              close(fd[0]);
                              return success;
                         }
                         else
                         {
                              argformer(Arguments, Tree->args);
                              success = execv("Wc.exe", Arguments);
                              printf("command error in %s\n", Tree->args->arg1);
                              write(fd[1], &success, 1);
                              raise(SIGKILL);
                         }
                    }
                    else
                         if (strcmp(Tree->args->arg1, "cat") == 0)
                         {
                              int fd[2];
                              pipe(fd);
                              if (fork() > 0)
                              {
                                   wait(NULL);
                                   close(fd[1]);
                                   read(fd[0], &success, 1);
                                   close(fd[0]);
                                   return success;
                              }
                              else
                              {
                                   argformer(Arguments, Tree->args);
                                   success = execv("Cat.exe", Arguments);
                                   printf("command error in %s\n", Tree->args->arg1);
                                   write(fd[1], &success, 1);
                                   raise(SIGKILL);
                              }
                         }
               int fd[2];
               pipe(fd);
               if (fork() > 0)
               {
                    wait(NULL);
                    close(fd[1]);
                    read(fd[0], &success, 1);
                    close(fd[0]);
               }
               else
               {
                    argformer(Arguments, Tree->args);
                    success = execvp(Tree->args->arg1, Arguments);
                    printf("command error in %s\n", Tree->args->arg1);
                    write(fd[1], &success, 1);
                    raise(SIGKILL);
               }
               break;
          }
          default:
          {
               error("unexpected Lex value...\n");
               return -1;
          }
     }
     return success;
}
