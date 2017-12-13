Lex nextlex(char * cur_str)
{
     char c;
     skip(&c);
     cur_str[0] = '\0';
     if (c == '\0')
          return _eoln;
     switch (c)
     {
          case '&':
          {
               read(0, &c, 1);
               if (c == '&')
                    return _and;
               else
                    return _background;
               break;
          }
          case '|':
          {
               read(0, &c, 1);
               if (c == '|')
                    return _or;
               else
                    return _pipe;
               break;
          }
          case '>':
          {
               read(0, &c, 1);
               if (c == '>')
               {
                    cur_str[0] = '>';
                    cur_str[1] = '>';
                    cur_str[2] = '\0';
                    return _redirect;
               }
               else
               {
                    cur_str[0] = '>';
                    cur_str[1] = '\0';
                    return _redirect;
               }
               break;
          }
          case '<':
          {
               cur_str[0] = '<';
               cur_str[1] = '\0';
               return _redirect;
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
                      (c != '<')
                    )
               {
                    buf[i] = c;
                    read(0, &c, 1);
                    i++;
               }
               ungetc(c, stdin);
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
