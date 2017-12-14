char ** string_demolisherXXX(char * args)
{
     char c;
     char * demolished_args[BUFSIZE];
     int i = 0, j = 0;
     char ** p = (char **) calloc (1, sizeof(char *));
     do
     {
          demolished_args[j] = (char *) calloc (BUFSIZE, sizeof(char));
          do
          {
               c = args[i];
               demolished_args[j][i] = c;
               i++;
          }
          while ((c != ' ') && (c != '\0'));
          demolished_args[j][i - 1] = '\0';
          j++;
     }
     while (c != '\0');
     *p = demolished_args[0];
     return p;
}
